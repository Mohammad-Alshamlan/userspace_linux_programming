#include<stdio.h>	// for printf()
#include<stdlib.h>	// for exit()
#include<string.h>	// for memset()
#include<sys/types.h>	// ???
#include<sys/socket.h>	// ???
#include<netinet/in.h>	// ???
#define MYPORT 3334

int main()
{
	int sockfd;	/*	socket file descriptor	*/
	struct sockaddr_in my_addr;
	//
	//sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if ( (sockfd = socket(AF_INET /* selecting ip4 */, SOCK_STREAM /* selecting TCP/IP */, 0)) == -1 ) {
		perror("Server-socket() error lol");
		exit(1);
	} else
		printf("Server-socket() sockfd is OK...\n");
	/* host byte order */
	my_addr.sin_family = AF_INET ;
	/* short, network byte order */
	my_addr.sin_port = htons(MYPORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	/*  zero the rest of the struct */
	memset( &(my_addr.sin_zero), 0, 8);
	// bind a name to socket
	if (bind(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) == -1) {
		perror("Server-bind() error lol!");
		exit(1);
	} else 
		printf("Server-bind() is OK...\n");
		
	/* ... other codes ... */
	
	return 0;
}
