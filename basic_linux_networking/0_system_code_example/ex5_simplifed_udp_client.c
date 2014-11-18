/*
 * write a client recives a message from the server and prints it out?
 * Note, it is missing error checks!!
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 5000
#define MAX_MESSAGE 512
#define HOSTNAME "localhost"

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
	int sockfd = socket(hostname->h_addrtype, SOCK_DGRAM, 0);
	// prepar the message to the client
	char sendBuff[MAX_MESSAGE];
	memset(sendBuff, 0, sizeof(sendBuff)); 	
        sprintf(sendBuff, "Hello World!!");
	// send the message to the server
	sendto(sockfd, sendBuff, sizeof(sendBuff) -1, 0, (struct sockaddr *) &server, sizeof(server));	
	// done!!
	close(sockfd); 
	return 0;
}

