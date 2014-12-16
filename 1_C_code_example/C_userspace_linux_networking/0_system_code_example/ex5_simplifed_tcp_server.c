/*
 * write the simplest TCP program as possible: send "hello World!!" from server to client through TCP/IP
 * Note, it is missing error checks!! Bad!!!
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 5000
#define MAX_MESSAGE 512
#define BACKLOG 5

int main(int argc, char *argv[])
{
	// create a struct sockaddr_in for server!!
	struct sockaddr_in server; 
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(PORT); 
	// create a server socket -- needs error check!!
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	// bind() -- needs error check!!
	bind(server_fd, (struct sockaddr*)&server, sizeof(server)); 
	// listen() -- needs error check!!
	listen(server_fd, BACKLOG); 
	// accept!! -- needs error check!!
	int client_fd = accept(server_fd, (struct sockaddr*)NULL, NULL); 
	// send a message to the client!!
	char sendBuff[MAX_MESSAGE];
	memset(sendBuff, 0, sizeof(sendBuff)); 	
        sprintf(sendBuff, "Hello World!!\n");
        write(client_fd, sendBuff, strlen(sendBuff)); 
	// we don't need the socket that are associated with the client and server anymore!! 
        close(client_fd);
	close(server_fd);
	return 0;
}

