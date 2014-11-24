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
#include<unistd.h>

#ifndef PORT
#define PORT 1234
#endif

#ifndef MESSAGE_SIZE
#define MESSAGE_SIZE 128
#endif

int main(int argc, char *argv[])
{
	// create strcut scoaddr_in server
	struct sockaddr_in client, server;
	memset(&server, 0, sizeof(server));
	server.sin_family=AF_INET;
	server.sin_port= htons(PORT);
	server.sin_addr.s_addr= htonl(INADDR_ANY);	
	// create the socket()
	int server_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(server_fd == -1){
		perror("socket() failed!!");
		return 1;
	}
	// bind()
	int rc = bind(server_fd, (struct sockaddr*)& server, sizeof(server));
	if(rc){
		perror("bind() failed!!");
		close(server_fd);
		return 1;
	}
	// receive the client message
	char message[MESSAGE_SIZE];
	memset(message, 0, sizeof(message));
	socklen_t client_len;
	rc = recvfrom(server_fd, message, sizeof(message), 0, (struct sockaddr*)&client, &client_len);
	if(rc < 0){
		perror("recvfrom() failed!!");
		close(server_fd);
		return 1;
	}
	// printout the received message from the client
	printf("received message: %s\n", message);
	// let echo the received message
	rc = sendto(server_fd, message, strlen(message), 0, (struct sockaddr*)&client, client_len);
	if(rc < 0){
		perror("sendto() failed!!");
		close(server_fd);
		return 1;
	}
	// done!!
	close(server_fd);
	return 0;

}
