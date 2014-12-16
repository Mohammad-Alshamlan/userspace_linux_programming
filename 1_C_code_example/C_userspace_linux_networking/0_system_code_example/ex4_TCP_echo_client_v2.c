#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define PORT 1234
#define HOSTNAME "localhost"

int main(int argc, char *argv[])
{
	// setting up local variables
	int sockfd, n;
	struct sockaddr_in serv_addr;
	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	struct hostent *server;
	char buffer[256];
	// creating a socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		perror("ERROR opening socket");
		return 1;	
	} 
	// getting the IP address from the DNS loookup table
	server = gethostbyname(HOSTNAME);
	// setting up port and IP address
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_family = AF_INET; 
	memcpy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	// connect() to the server 
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
		perror("ERROR connecting");
		return 1;	
	} 
	// get a string from the client
	printf("Please enter the message: ");
	memset(buffer,0, sizeof(buffer));
	fgets(buffer,sizeof(buffer) -1 ,stdin);
	// send the srting to the server
	n = write(sockfd,buffer,strlen(buffer));
	if (n < 0) {
		perror("ERROR writing to socket");
		return 1;	
	} 	
	// get the server responds and prints it out
	memset(buffer,0, sizeof(buffer));
	n = read(sockfd,buffer,sizeof(buffer) -1);
	if (n < 0) {
		perror("ERROR reading from socket");
		return 1;	
	} 	
	printf("%s\n",buffer);
	// close
	close(sockfd);
	return 0;
}
