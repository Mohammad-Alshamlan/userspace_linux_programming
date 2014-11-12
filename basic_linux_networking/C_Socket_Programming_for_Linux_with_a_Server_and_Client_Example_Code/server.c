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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

int main(int argc, char *argv[])
{
    // create and set the local var, which includes the socket descriptor
    int listenfd = 0, connfd = 0;
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
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
	// 
        ticks = time(NULL);
        snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
        write(connfd, sendBuff, strlen(sendBuff)); 

        close(connfd);
        sleep(1);
     }
     // done!!
     close(listenfd);
     return 0;
}
