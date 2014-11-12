/*
 * So, if you're going to be listening for incoming connections, the sequence of the system calls you'll make is something like this
 * 
 *	socket()
 *	bind()
 *	listen()
 *	// accept() goes here
 *	// after you done with the socket, to unlack resources, use close()
 *	// note, shutdown() change the socket RX, TX, or both. However, shutdown() doesn't unlack the resource of the socket, so close()
 *	// must be used even though the socket RX and TX has been shutdowned by showdown()
 */
  
#include<stdio.h>	// for printf()
#include<stdlib.h>	// for exit()
#include<string.h>	// for memset()
#include<sys/types.h>	// ???
#include<sys/socket.h>	// ???
#include<netinet/in.h>	// ???
/* the port users will be connecting to	*/
#define MYPORT 3440
/* how many pending connections queue will hold */
#define BACKLOG 10

int main()
{
	/* listen on sock_fd, new connection on new_fd */
	int sockfd, new_fd;	/*	socket file descriptor	*/
	/* my address infomation, address where I run this program */
	struct sockaddr_in my_addr;
	/* remote address information */
	struct sockaddr_in their_addr;
	int sin_size;
	// creating the socket
	sockfd = socket (AF_INET /* selecting ip4 */, SOCK_STREAM /* selecting TCP/IP */, 0);
		if ( sockfd == -1 ) {
		perror("Server-socket() error lol");
		exit(1);
	} else
		printf("Server-socket() sockfd is OK...\n");
	/* host byte order */
	my_addr.sin_family = AF_INET ;
	/* short, network byte order */
	my_addr.sin_port = htons(MYPORT);
	/* auto-fill with my IP */
	my_addr.sin_addr.s_addr = INADDR_ANY;
	/*  zero the rest of the struct */
	memset( &(my_addr.sin_zero), 0, 8);
	
	// bind a name to socket
	if (bind(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) == -1) {
		perror("Server-bind() error lol!");
		exit(1);
	} else 
		printf("Server-bind() is OK...\n");
		
	/* listen to the binded socket */
	if(listen(sockfd, BACKLOG) == -1)
	{
		perror("listen() error lol!!");
		exit(1);
	} else 
		printf("listen() is OK...\n");
		
	/* ... other codes to read the received data... */
	sin_size = sizeof(struct sockaddr_in);
	new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &sin_size);
	
	if(new_fd == -1)
		perror("accept() error lol!");
	else 
		printf("accept() is OK...\n");
		
		
	/* ... other codes ... */
	
	close(new_fd);
	close(sockfd);
	return 0;
}

/*
// output

alshamlan@alshamlan-OptiPlex-980:/tmp/code$ make TCP_IP_using_socket_bind_listen
make: `TCP_IP_using_socket_bind_listen' is up to date.
alshamlan@alshamlan-OptiPlex-980:/tmp/code$ make -B TCP_IP_using_socket_bind_listen
cc     TCP_IP_using_socket_bind_listen.c   -o TCP_IP_using_socket_bind_listen
alshamlan@alshamlan-OptiPlex-980:/tmp/code$ ./TCP_IP_using_socket_bind_listen
Server-socket() sockfd is OK...
Server-bind() is OK...
listen() is OK...

^C
alshamlan@alshamlan-OptiPlex-980:/tmp/code$ 

*/
