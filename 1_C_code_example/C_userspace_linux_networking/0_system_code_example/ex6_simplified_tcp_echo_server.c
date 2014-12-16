#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>


#ifndef PORT
#define PORT 1234
#endif

#ifndef BACKLOG
#define BACKLOG 5
#endif

#define MAX_MESSAGE 128

int main(int argc, char *argv[])
{
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
	// write hello world!! to the client
	char message[MAX_MESSAGE];
	memset(message, 0, sizeof(message));
	sprintf(message, "Hello World!!");
	rc= write(client_fd, message, strlen(message));
	if(rc == 0){
		perror("write() failed!!");
		return 1;
	}
	// let receive the echoed massage from the client
	memset(message, 0, sizeof(message));	
	rc = read(client_fd, message, sizeof(message));
	if(rc == 0){
		perror("read() failed!!");
		return 1;
	}
	// let printout the echoed message from the client
	printf("echoed message from the client: %s\n", message);
        // let the client knows that we are done!!
        shutdown(client_fd,SHUT_RDWR); 	
	// done!!
	close(client_fd);
	close(fd);
	return 0;
}
