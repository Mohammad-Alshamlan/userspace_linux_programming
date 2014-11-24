/**********************************************************************************
 * The idea is to write down a simplified echo udp server and client as possible!!*
 **********************************************************************************
 *
 * workflow:
 *	<client>	===sending a message===>>		<server>
 *	<client>	<<===receiving echoed message==		<server>
 *
 * instruction:
 *	[1] run the server as follows:
 *		(bash) $ ./udp_echo_server
 *	[2] open a new terminal for the client
 *	[3] run the client with the hostname such as the following:
 *		(bash) $ ./udp_echo_client `hostname`
 *	[4] now you can chat
 *	[5] if you want to exit, then there two ways:
 *		1. using "exit" instruction
 *		2. pressing <ctrl> + 'd' which is EOF
 *
 * Example, 
 * " server"
 *	alshamlan@alshamlan-Precision-M6700:/tmp/interview$ ./udp_server 
 *	waiting for the client!!
 *	received message:	hello world!!
 *	received message:	exit
 *	exit instruction has been requested!!
 *	alshamlan@alshamlan-Precision-M6700:/tmp/interview$ 
 *
 * "client"
 *	alshamlan@alshamlan-Precision-M6700:/tmp/interview$ ./udp_client `hostname`
 *	Please, enter text:		hello world!!
 *	The received echoed message:	hello world!!
 *	Please, enter text:		exit
 *	 
 *	The received echoed message:	exit
 *	client is exiting now!!
 *	alshamlan@alshamlan-Precision-M6700:/tmp/interview$	
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
	// let implement the echo udp server
	printf("waiting for the client!!\n");
	char message[MESSAGE_SIZE];
	socklen_t client_len;
	do{
		// why this is needed!!
		client_len = sizeof(client);
		memset(message, 0, sizeof(message));	
		rc = recvfrom(server_fd, message, sizeof(message), 0, (struct sockaddr *)&client,&client_len);
		if(rc < 0){
			perror("recvfrom() failed!!");
			close(server_fd);
			return 1;
		}
		// print the received message
		printf("received message:\t%s", message);
		// echo the received message back to the server
		rc = sendto(server_fd, message, strlen(message), 0, (struct sockaddr*)&client, client_len);
		if(rc < 0){
			perror("sendto() failed!!");
			close(server_fd);
			return 1;
		}
		// let have an exit instruction if a string is empty
	} while (strcmp(message, "exit") != 0);
	// done!!
	printf("\nexit instruction has been requested!!\n");
	close(server_fd);
	return 0;

}
