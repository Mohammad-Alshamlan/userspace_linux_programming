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
 */

#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>

#ifndef PORT
#define PORT 1234
#endif

#ifndef MESSAGE_SIZE
#define MESSAGE_SIZE 128
#endif

int main(int argc, char *argv[])
{
	// check the command-line argument
	if(argc < 2){
		fprintf(stderr, "please the command as follows:\n\t(bash) $ %s <hostname or ip>\n", argv[0]);
		return 0;
	}
	// let got the IP address 
	struct hostent *hostname = gethostbyname(argv[1]);
	if (hostname == NULL){
		perror("gethostbyname(argv[1]) failed!!");
		return 1;
	}
	// create and define struct sockaddr_in 
	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr= *((struct in_addr*) hostname->h_addr);
	// create a socket()
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1){
		perror("socket() failed!!");
		return 1;
	}
	// connect()
	int rc = connect(fd, (struct sockaddr*)&server, sizeof(server));
	if(rc){
		perror("connect() failed!!");
		close(fd);
		return 1;
	}
	// let implement tcp echo client
	char message[MESSAGE_SIZE];
	int *eof;
	do{
		printf("Please, enter text:\t\t");
		// let get a newline for the user
		eof = (int *) fgets(message, sizeof(message), stdin);
		if ( (eof == NULL) || (strcmp(message, "exit\n") == 0)){
			// this means the client wants to exit, so let make the server knows about this
			sprintf(message, "exit");
			// just newline for style
			puts(" ");
		}
		// let send the messge to the server
		rc = write(fd, message, strlen(message));
		if(rc == 0){
			perror("write() failed!!");
			close(fd);
			return 1;
		}
		// let reset the messgae buffer -- make sure that we received the echoed message from the server!!
		memset(message, 0, sizeof(message));		
		// let received the echoed message back for the server
		rc = read(fd, message, sizeof(message));
		if(rc == 0){
			perror("read() failed!!");
			close(fd);
			return 1;
		}
		// printout the received echoed text
      		printf("The received echoed message:\t%s", message);		
	} while (strcmp(message, "exit") != 0);
	// done!!
	printf("\nclient is exiting now!!\n");
	close(fd);
	return 0;
}
