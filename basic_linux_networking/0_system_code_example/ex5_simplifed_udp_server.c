/*
 * write the simplest UDP program as possible: get "hello World!!" from client through UDP/IP
 * Note, it is missing error checks!! Bad!!!
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 5000
#define MAX_MESSAGE 512

int main(int argc, char *argv[])
{
	// create a struct sockaddr_in for client!!
	struct sockaddr_in client; 
	memset(&client, 0, sizeof(client));
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = htonl(INADDR_ANY);
	client.sin_port = htons(PORT); 
	// create a client socket -- needs error check!!
	int client_fd = socket(AF_INET, SOCK_DGRAM, 0);
	// bind() -- needs error check!!
	bind(client_fd, (struct sockaddr*)&client, sizeof(client)); 
	// get the message to the client
	int n;
	char sendBuff[MAX_MESSAGE];
	memset(sendBuff, 0, sizeof(sendBuff)); 		
	n = recvfrom(client_fd, sendBuff, sizeof(sendBuff) -1, 0, NULL, NULL);
	sendBuff[n]='\0';
	// output the message
	printf("%s\n", sendBuff);
	// close the socket
	close(client_fd);
	return 0;
}


