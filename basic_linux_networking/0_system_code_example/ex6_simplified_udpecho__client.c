/*
 * The idea is to write down a simplified echo udp server and client as possible!!
 *
 * workflow:
 *	<client>	===sending a message===>>		<server>
 *	<client>	<<===receiving echoed message==		<server>
 */

#include<netinet/in.h>
#include<string.h>
#include<sys/socket.h>
#include<stdio.h>
#include <netdb.h>
#include<unistd.h>


#ifndef PORT
#define PORT 1234
#endif

#ifndef MESSAGE_SIZE
#define MESSAGE_SIZE 128
#endif

#ifndef HOSTNAME
#define HOSTNAME "localhost"
#endif

int main(int argc, char *argv[])
{
	// struct hostent to enable hostname (DNS) and get server IP address
	struct hostent *hostname = gethostbyname(HOSTNAME) ;
	// creating internet socket by using struct sockaddr_in
	struct sockaddr_in server; 
	memset(&server, 0, sizeof(server)); 
	server.sin_family = hostname->h_addrtype;	// most likey it is AF_INET
	server.sin_port = htons(PORT);			// hard-coded port
	server.sin_addr = *((struct in_addr *) hostname->h_addr); // get the IP after converting the hostname
	// create a socket 
	int fd = socket(hostname->h_addrtype, SOCK_DGRAM, 0);
	if(fd == -1){
		perror("socket() failed!!");
		return 1;
	}
	// send a message to the server
	char message[MESSAGE_SIZE];
	memset(message, 0, sizeof(message));
	sprintf(message, "Hello World!!");
	int rc = sendto(fd, message, strlen(message), 0, (struct sockaddr*)&server, sizeof(server));
	if(rc < 0){
		perror("sendto() failed!!");
		close(fd);
		return 1;
	}
	// now, let receive the echoed message
	memset(message, 0, sizeof(message));
	rc = recvfrom(fd, message, sizeof(message), 0, NULL, NULL);
	if(rc < 0){
		perror("recvfrom() failed!!");
		close(fd);
		return 1;	
	}
	// let print out the echoed message 
	printf("the received echoed message: %s\n", message);
	// done!!
	close(fd);
	return 0;
}
