#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include <netdb.h>

#ifndef PORT
#define PORT 1234
#endif

#ifndef MAX_MESSAGE
#define MAX_MESSAGE 128
#endif

int main(int argc, char *argv[])
{
	// check if the server address is inputted!!
	if(argc < 2){
		fprintf(stderr, "error: please run the following \n\t(bash) $ %s <hostname> \n", argv[0]);
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
	int rc = connect(server_fd, (struct sockaddr *) &server_address, sizeof(server_address));
	if(rc){
		perror("connect() failed!!");
		return 0;
	}
	// let read the message from the server
	char message[MAX_MESSAGE];
	memset(message, 0, sizeof(message));
	rc = read (server_fd, message, sizeof(message));
	if(rc == 0){
		perror("read() failed!!");
		return 1;
	}
	// printout the received message from the server
	printf("received from the server: %s\n", message);
	// now, let echo the message back to the server
	rc = write (server_fd, message, strlen(message));
	if(rc == 0){
		perror("write() failed!!");
		return 1;
	}
	// done!!
	close(server_fd);
	return 0;
}
