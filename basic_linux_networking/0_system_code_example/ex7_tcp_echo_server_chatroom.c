/**********************************************************************************
 * The idea is to write down a simplified echo tcp server and client as possible!!*
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
 * 
 * to-do-list:
 *	[1] the server just talks to the first client and ignores other clients that came after the first one needs a fix
 */

#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/socket.h>

#ifndef PORT
#define PORT 1234
#endif

#ifndef BACKLOG
#define BACKLOG 5
#endif

#ifndef MESSAGE_SIZE
#define MESSAGE_SIZE 128
#endif

int main(int argc, char *argv[])
{
	// create and define struct sockaddr_in 
	struct sockaddr_in client;
	memset(&client, 0, sizeof(client));
	client.sin_family=AF_INET;
	client.sin_port=htons(PORT);
	client.sin_addr.s_addr=htonl(INADDR_ANY);
	// create a socket()
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1){
		perror("socket() failed!!");
		return 1;
	}
	// bind()
	int rc = bind(fd, (struct sockaddr*)&client, sizeof(client));
	if(rc){
		perror("bind() failed!!");
		close(fd);
		return 1;
	}
	// listen()
	rc = listen(fd, BACKLOG); 
	if(rc){
		perror("listen() failed!!");
		close(fd);
		return 1;	
	}
	// wait to a client to connect	
	printf("waiting for the client!!\n");
	int client_fd = accept(fd, (struct sockaddr*)NULL, NULL);
	if(client_fd == 0){
		perror("accept() failed!!");
		close(fd);
		return 1;
	}
	// let implement the echo server 
	char message[MESSAGE_SIZE];
	do {
		// reset the buffer
		memset(message, 0, sizeof(message));
		// received a message from the client
		rc = read (client_fd, message, sizeof(message));
		if(rc == 0){
			perror("read() failed!!");
			close(fd);
			close(client_fd);
			return 1;
		}
		// let printout the received message before we echo it back to the client
		printf("the received message:\t%s",message);
		// close the client
		rc = write (client_fd, message, strlen(message));
		if(rc == 0){
			perror("write() failed!!");
			close(fd);
			close(client_fd);
			return 1;			
		}		
	} while (strcmp(message, "exit") != 0);
	// done!!
	printf("\nexit instruction has been requested!!\n");
	close(fd);
	close(client_fd);
	return 0;	
}
