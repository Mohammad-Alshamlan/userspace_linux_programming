/* 
 * the idea is to transfer picture through TCP socket()
 * I want the name to be transfer also with the file extension
 */

#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<libgen.h>

#ifndef PORT
#define PORT 1234
#endif

#ifndef BACKLOG
#define BACKLOG 5
#endif

#define MAX_MESSAGE 512

int main(int argc, char *argv[])
{
	// check if we have the right number of arguments
	if(argc < 2){
		fprintf(stderr, "you're missing the filename. Please, run it as follows:\n\t(bash) $ %s <filename>\n", argv[0]);
		return 1;
	}
	// extract the filename with file extension (i.e .txt) from the pathname if needed
	char *filename = basename(argv[1]);
	// open the source file, and make sure it is opened correctly
	int fd_src = open(argv[1], O_RDONLY);
	if(fd_src == -1){
		perror("opening fd_src failed!!");
		return 1;
	}	
	// setup struct sockaddr_in
	struct sockaddr_in client;
	memset(&client, 0, sizeof(client));
	client.sin_port=htons(PORT);
	client.sin_addr.s_addr=htonl(0); // localhost bad!!!
	client.sin_family = AF_INET;
	// create socket()
	int fd = socket(client.sin_family, SOCK_STREAM, 0);
	if (fd == -1){
		perror("socket() failed!!");
		return 1;
	}
	// bind()
	int rc = bind(fd, (struct sockaddr *)&client, sizeof(client));
	if(rc){
		perror("bind() failed!!");
		return 1;
	}
	// listen()
	rc = listen(fd , BACKLOG);
	if(rc){
		perror("listen() failed!!");
		return 1;
	}	  
	// accept()
	int client_fd = accept(fd, (struct sockaddr *)NULL, NULL);
	// first let use send the filename
	char message[MAX_MESSAGE];
	memset(message, 0, sizeof(message));
	sprintf(message, "cloned_%s", filename);
	rc= write(client_fd, message, strlen(message));
	if(rc == 0){
		perror(" sending the filename to client failed!!");
		return 1;
	}
	// Now, let send the image -- copy from the source file to destination file
	memset(message, 0, sizeof(message));	
	size_t read_len = 0, write_len=0; 
	while((read_len = read(fd_src, message, sizeof(message))) > 0){
		write_len = write(client_fd, message, read_len);
		// check if it isn't partial write
		if(read_len != write_len){
			perror("partail write!!");
			return 1;
		}
	}	
        // let the client knows that we are done!!
        shutdown(client_fd,SHUT_RDWR); 	
	// done!!
	close(fd_src);	
	close(client_fd);
	close(fd);
	return 0;
}
