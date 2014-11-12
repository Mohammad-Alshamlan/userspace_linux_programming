/*
 *
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

#define HARD_CODED_PORT 5000

int main(int argc, char *argv[])
{
	int sockfd = 0, n = 0;
	char recvBuff[1024];
	memset(recvBuff, 0,sizeof(recvBuff));
	// socket local var 
	struct hostent *hostname;
	struct sockaddr_in serv_addr; 
	memset(&serv_addr, 0, sizeof(serv_addr)); 
	// check if we have the right number of arguments	
	if(argc != 2) {
		printf("\n Usage: %s <ip of server> \n",argv[0]);
		return 1;
	} 
	// get the server IP even if it is a hostname 
	if ((hostname = gethostbyname(argv[1])) == NULL) {  // get the host info
        	herror("gethostbyname");
        	return 2;
	}
	// configure the socket struct
	serv_addr.sin_family = hostname->h_addrtype;	// most likey it is AF_INET
	serv_addr.sin_port = htons(HARD_CODED_PORT);	// hard-coded port
	memcpy(&(serv_addr.sin_addr.s_addr), hostname->h_addr, hostname->h_length);

	// create a socket
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Error : Could not create socket \n");
		return 1;
	} 
	// 
#if 0
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); 
    // check if given address is correct
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 
#endif
    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 

    while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
    {
        recvBuff[n] = 0;
        if(fputs(recvBuff, stdout) == EOF)
        {
            printf("\n Error : Fputs error\n");
        }
    } 

    if(n < 0)
    {
        printf("\n Read error \n");
    } 

    return 0;
}


