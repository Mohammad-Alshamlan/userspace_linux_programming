#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include <netdb.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#ifndef PORT
#define PORT 1234
#endif

#ifndef MAX_MESSAGE
#define MAX_MESSAGE 512
#endif

#ifndef DEST_FILE
#define DEST_FILE "dest_file.jpeg"
#endif

int main(int argc, char *argv[])
{
	// check if the server address is inputted!!
	if(argc < 2){
		fprintf(stderr, "error: please run the following \n\t(bash) $ %s <hostname> \n", argv[0]);
		return 1;
	}
	// delete the previous image if exist
	int rc = unlink(DEST_FILE);
	#if 0
	if(rc){
		perror("unlink() failed!!");
		return 0;
	}	
	#endif
	// open the destination file (or create it), and make sure it is opened correctly
	int fd_dest = open(DEST_FILE, O_WRONLY | O_CREAT);
	if(fd_dest == -1){
		perror("opening fd_src failed!!");
		return 1;
	}	
	// get the server IP from server DNS
	struct hostent *server_hostname=NULL;
	server_hostname = gethostbyname(argv[1]);
	if(server_hostname == 0){
		perror("gethostbyname() failed!!");
		return 1;
	}
	// create and define stuct sockaddr_in
	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_port=htons(PORT);
	server_address.sin_family=server_hostname->h_addrtype;
	server_address.sin_addr= *((struct in_addr *) server_hostname->h_addr);
	// create the server socket
	int server_fd= socket(server_hostname->h_addrtype, SOCK_STREAM, 0);
	if(server_fd == -1){
		perror("socket() failed!!");
		return 1;
	}
	// connect()
	rc = connect(server_fd, (struct sockaddr *) &server_address, sizeof(server_address));
	if(rc){
		perror("connect() failed!!");
		return 0;
	}
	// get the file from the source file to destination file
	char message[MAX_MESSAGE];
	memset(message, 0, sizeof(message));
	size_t read_len = 0, write_len=0; 
	while((read_len = read(server_fd, message, sizeof(message)) ) > 0){
		write_len = write(fd_dest, message, read_len);
		// check if it isn't partial write
		if(read_len != write_len){
			perror("partail write!!");
			return 1;
		}
	}
	// close the socket and file 
	close(fd_dest);	
	close(server_fd);
	// I got this premission
		/*
		(bash) $ ls -lsh *j*
			20K -r-x-wS--T 1 alshamlan alshamlan 9.2K Dec 16 17:22 dest_file.jpeg
			24K -rw-r----- 1 alshamlan alshamlan 9.2K Dec 16 11:56 images.jpg	
		*/
	// So, let reset the file premission 
	rc = chmod(DEST_FILE, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	// done!!
	return 0;
}
