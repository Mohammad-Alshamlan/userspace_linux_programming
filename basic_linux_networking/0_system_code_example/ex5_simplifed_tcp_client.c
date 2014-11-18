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
	int sockfd = socket(hostname->h_addrtype, SOCK_STREAM, 0);
	// connect() the socket
	connect(sockfd, (struct sockaddr *)&server, sizeof(server));
	// read() the message from server!!
	int n = 0;
	char recvBuff[MAX_MESSAGE];
	memset(recvBuff, 0,sizeof(recvBuff));	
	n = read(sockfd, recvBuff, sizeof(recvBuff)-1);
	recvBuff[n] = 0;
	// print the info on printf
	if(fputs(recvBuff, stdout) == EOF) 
		printf("\n Error : Fputs error\n");
	// done!!
	close(sockfd); 
	return 0;
}

