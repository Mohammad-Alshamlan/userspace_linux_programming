/*
 * Let create a server that continuously runs and sends the date and time as soon as 
 * a client connects to it.
 * 
 * Example 1:
 * [1] first open two terminals, let call them terminal x and y
 *	(terimanl x) $ ./server
 *	(terimanl y) $ ./client 127.0.0.1
 *
 * Example 2: use hostname command
 *	(terimanl x) $ ./server
 *	(terimanl y) $ ./client `hostname`
 * to-do-list:
 * [1] add error checks!!
 */

// I used these before
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h> 
#include <sys/types.h>
// these are new to me!!
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    // create and set the local var, which includes the socket descriptor
    int listenfd = 0, connfd = 0, rc=0;
    struct sockaddr_in serv_addr; 
    char sendBuff[1025];
    time_t ticks;
    memset(&serv_addr, 0, sizeof(serv_addr));
    memset(sendBuff, 0, sizeof(sendBuff)); 
    // create a socket and set it up
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 
    // bind()
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
    // listen()
    listen(listenfd, 10); 

    while(1)
    {
        /* 
         *         #include <sys/types.h>          
         *	   #include <sys/socket.h>
	 *
         *	   int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
         *
         * The argument addr is a pointer to a sockaddr structure.  This structure is filled in with the address of the peer socket, as known to the communications layer.  
         * The exact format of the address returned addr is determined by the socket's address family (see socket(2) and the respective protocol man pages).  
         * When addr is NULL, nothing is filled in; in this case, addrlen is  not  used, and should also be NULL.
         *
         * source: 
         *	(bash) $ man 2 accept
         *
         */
        rc = connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
        if (rc == -1) {
		perror("Client-connect() error lol!");
		exit(1);
	} else 
		printf("Client-connect() is OK...\n");
	// get wall-time!!
        ticks = time(NULL);
        snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
        rc = write(connfd, sendBuff, strlen(sendBuff)); 
        if(rc == -1){
        	perror("sending time to client has failed!");
        } else 
        	printf("this is how many words have been sent: %d\n", rc);
	// we don't need the socket that is associated with the client anymore!! 
        close(connfd);
        // let sleep to prevent spinlock
        sleep(1);
     }
     // done!! closing the server socket
     close(listenfd);
     return 0;
}
