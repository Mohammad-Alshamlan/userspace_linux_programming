/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 1234
#define HOSTNAME "localhost"

int main(int argc, char *argv[])
{
	// setting up local variables
	int sockfd, newsockfd; 
	socklen_t clilen;
	char buffer[256], buffer_2[sizeof(buffer)];
	struct sockaddr_in serv_addr, cli_addr;
	memset((char *) &serv_addr,0, sizeof(serv_addr));
	int n;
	// create socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		perror("ERROR opening socket");
		return 1;	
	} 
	// getting the port number form argv[1]
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(PORT);
	// bind()
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		perror("ERROR on binding");
		return 1;	
	} 	
	// listen(): why using 5, when the first connection will kill the server!!
	listen(sockfd,5);
	// setting up the client socket()	
	clilen = sizeof(cli_addr);
	printf("the server is wating for the client!\n");
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd < 0) {
		perror("ERROR on accept");
		return 1;	
	} 	
	printf("client is now connected, and the server is still wauiting for client message!!\n");
	// get a string from the client 
	memset(buffer,0, sizeof(buffer));
	n = read(newsockfd,buffer,sizeof(buffer) -1);
	if (n < 0) {
		perror("ERROR reading from socket");
		return 1;	
	} 
	// print the received message from the client onto the server screen!!
	printf("Here is the message: %s\n",buffer);
	// echo the client message back to the client
	memset(buffer_2, 0, sizeof(buffer_2));
	sprintf(buffer_2, "echoed message: %s", buffer);
	n = write(newsockfd, buffer_2, strlen(buffer_2));
	if (n < 0) {
		perror("ERROR writing to socket");
		return 1;	
	} 	
	// done!!
	close(newsockfd);
	close(sockfd);
	return 0; 
}
