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
#include <netdb.h>
#include<unistd.h>


#ifndef PORT
#define PORT 1234
#endif

#ifndef MESSAGE_SIZE
#define MESSAGE_SIZE 128
#endif


int main(int argc, char *argv[])
{
	// check if the host is included in the commmand-line or not
	if(argc < 2){
		fprintf(stderr, "please run the command as follows\n\t(bash) $ %s <hostname>\n", argv[0]);
		return 1;
	}
	// struct hostent to enable hostname (DNS) and get server IP address
	struct hostent *hostname = gethostbyname(argv[1]) ;
	// creating internet socket by using struct sockaddr_in
	struct sockaddr_in server; 
	memset(&server, 0, sizeof(server)); 
	server.sin_family = hostname->h_addrtype;	// most likey it is AF_INET
	server.sin_port = htons(PORT);			// hard-coded port
	server.sin_addr = *((struct in_addr *) hostname->h_addr); // get the IP after converting the hostname
	// create a socket 
	int fd = socket(hostname->h_addrtype, SOCK_DGRAM, 0);
	if(fd == -1){
		perror("socket() failed!!");
		return 1;
	}
	// now, let have the echo client 
	char message[MESSAGE_SIZE];
	memset(message, 0, sizeof(message));
	int rc, *eof; 
	do {
		printf("Please, enter text:\t\t");
		// get a newline of strings
		eof = (int *) fgets(message, MESSAGE_SIZE,stdin);
		if ( (eof == NULL) || (strcmp(message, "exit\n") == 0) ) {
			// this means that the input is EOF, so the client is going to exit, let the server exits with the client
			sprintf(message, "exit");
			// just newline for style
			puts(" ");
		}
		// send a message to the server
		rc = sendto(fd, message, strlen(message),0, (struct sockaddr*)&server, sizeof(server));
		if(rc < 0){
			perror("sendto() failed!!");
			close(fd);
			return 1;
		}
		// now, let receive the echoed message
		memset(message, 0, sizeof(message));
		rc = recvfrom(fd, message,MESSAGE_SIZE,0,NULL,NULL);
		if(rc < 0){
			perror("recvfrom() failed!!");
			close(fd);
			return 1;	
		}
      		// let output the echoed message
      		printf("The received echoed message:\t%s", message);
	} while (strcmp( message, "exit") != 0);
	// done!!
	printf("\nclient is exiting now!!\n");
	close(fd);
	return 0;
}
