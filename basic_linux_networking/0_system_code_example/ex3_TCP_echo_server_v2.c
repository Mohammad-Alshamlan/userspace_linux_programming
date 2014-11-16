/*
	echo server: TCP/IP sockets example
	get a connect: keep reading data from the socket, echoing
	back the received data.

	usage:	echoserver [-d] [-p port]
*/

#include <stdio.h>
#include <stdlib.h>	/* needed for os x */
#include <string.h>	/* for memset */
#include <sys/socket.h>
#include <arpa/inet.h>	/* for inet_ntoa */
#include <netinet/in.h>
#include <sys/errno.h>   /* defines ERESTART, EINTR */
#include <sys/wait.h>    /* defines WNOHANG, for wait() */
#include <unistd.h>

#define SERVICE_PORT	21234	/* hard-coded port number */

// why defining ERESTART==EINTR (which is from #include <sys/errno.h>) where we can use EINT directory!! 
#ifndef ERESTART
#define ERESTART EINTR
#endif

extern int errno;

/* serve: set up the service */
void serve(int port)
{
	int svc;        /* listening socket providing service */
	int rqst;       /* socket accepting the request */
	socklen_t alen;       /* length of address structure */
	struct sockaddr_in my_addr;    /* address of this service */
	struct sockaddr_in client_addr;  /* client's address */
	int sockoptval = 1;
	char hostname[128]; /* host name, for debugging */

	gethostname(hostname, 128);

	/* get a tcp/ip socket */
	/*   AF_INET is the Internet address (protocol) family  */
	/*   with SOCK_STREAM we ask for a sequenced, reliable, two-way */
	/*   conenction based on byte streams.  With IP, this means that */
	/*   TCP will be used */

	if ((svc = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("cannot create socket");
		exit(1);
	}

	/* we use setsockopt to set SO_REUSEADDR. This allows us */
	/* to reuse the port immediately as soon as the service exits. */
	/* Some operating systems will not allow immediate reuse */
	/* on the chance that some packets may still be en route */
	/* to the port. */

	setsockopt(svc, SOL_SOCKET, SO_REUSEADDR, &sockoptval, sizeof(int));

	/* set up our address */
	/* htons converts a short integer into the network representation */
	/* htonl converts a long integer into the network representation */
	/* INADDR_ANY is the special IP address 0.0.0.0 which binds the */
	/* transport endpoint to all IP addresses on the machine. */

	memset((char*)&my_addr, 0, sizeof(my_addr));  /* 0 out the structure */
	my_addr.sin_family = AF_INET;   /* address family */
	my_addr.sin_port = htons(port);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	/* bind to the address to which the service will be offered */
	if (bind(svc, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0) {
		perror("bind failed");
		exit(1);
	}

	/* set up the socket for listening with a queue length of 5 */
	if (listen(svc, 5) < 0) {
		perror("listen failed");
		exit(1);
	}

	printf("server started on %s, listening on port %d\n", hostname, port);

	/* loop forever - wait for connection requests and perform the service */
	alen = sizeof(client_addr);     /* length of address */

	for (;;) {
		while ((rqst = accept(svc, (struct sockaddr *)&client_addr, &alen)) < 0) {
			/* we may break out of accept if the system call */
			/* was interrupted. In this case, loop back and */
			/* try again */
			if ((errno != ECHILD) && (errno != ERESTART) && (errno != EINTR)) {
				perror("accept failed");
				exit(1);
			}
		}
		// printout the echoed massage, then close the new created socket from accept()
		printf("received a connection from: %s port %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        	shutdown(rqst, 2);    /* close the connection */
	}
}

void disconn(void);

int main(int argc, char **argv)
{
	// setup the port
	int port = SERVICE_PORT;
	// create the server
	serve(port);
	return 0;
}

