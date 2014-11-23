/*
 * the idea of this code is:
 *	1. let the server get the DNS (or IP) of the client 
 *	2. let use ncat as client, and we simply will just write the server code!! 
 *		>> ncat can be used as follow to be a client for this code:
 * 		(bash) $ ncat `hostname` 5000 -t
 *
 *
 * this code uses "ex5_simplifed_tcp_server.c" 
 * write the simplest TCP program as possible: send "hello World!!" from server to client through TCP/IP
 * Note, it is missing error checks!! Bad!!!
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 5000
#define MAX_MESSAGE 512
#define BACKLOG 5

// POSIX doesn't define any fixed upper limit on the size of buffer that might be needed, however, implementations often provide a macro called NI_MAXHOST for this purpose. For portability you should test whether this macro exists and provide your own value if it doesn't.
#ifndef NI_MAXHOST
#define NI_MAXHOST 1025
#endif

int Convert_an_IP_address_to_the_corresponding_domain_name_in_C(int client_fd, char *client_hostname, size_t client_hostname_len)
{
	struct sockaddr_storage addr;
	// addr_len will probably not be equal to sizeof(struct sockaddr_storage) once the call to getpeername() has completed
	socklen_t addr_len=sizeof(addr);
	int rc=getpeername(client_fd, (struct sockaddr*)&addr, &addr_len);
	if (rc != 0){
		perror("getpeername() didn't work!!");
		return 1;
	}
	rc = getnameinfo((struct sockaddr*) &addr, addr_len, client_hostname, client_hostname_len, 0,0,0 );
	if(rc){
		perror("getnameinfo() failed!!");
		return 1;
	}
	return 0;
}

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
	// Convert_an_IP_address_to_the_corresponding_domain_name_in_C
	int rc;
	char client_hostname[NI_MAXHOST];
	memset(client_hostname, 0, sizeof(client_hostname));
	rc = Convert_an_IP_address_to_the_corresponding_domain_name_in_C(client_fd, client_hostname, sizeof(client_hostname));
	if(rc){
		perror("my function failed!!");
		return 1;
	}
	printf("the client DNS (or IP) address is: %s\n",  client_hostname);
	// send a message to the client!!
	char sendBuff[MAX_MESSAGE];
	memset(sendBuff, 0, sizeof(sendBuff)); 	
        sprintf(sendBuff, "Hello World!!\n");
        write(client_fd, sendBuff, strlen(sendBuff));
        // let the client knows that we are done!!
        shutdown(client_fd,SHUT_RDWR); 
	// we don't need the socket that are associated with the client and server anymore!! 
        close(client_fd);
	close(server_fd);
	return 0;
}

