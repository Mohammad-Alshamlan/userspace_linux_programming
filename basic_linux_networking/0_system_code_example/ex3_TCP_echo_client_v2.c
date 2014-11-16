/*
	echoc: a demo of TCP/IP sockets connect

	usage:	client [-h serverhost] [-p port]
*/

#include <stdio.h>
#include <stdlib.h>	/* needed for os x*/
#include <string.h>	/* for strlen */
#include <netdb.h>      /* for gethostbyname() */
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define SERVICE_PORT	21234	/* hard-coded port number */


int fd;  /* fd is the file descriptor for the connected socket */

/* conn: connect to the service running on host:port */
/* return 0 on failure, non-zero on success */
int conn(char *host, int port)
{
	// host information for DNS name resolution
	struct hostent *hp;
	// address length when we get the port number 
	unsigned int alen;
	// create two sockets for server and client
	struct sockaddr_in myaddr;	/* our address */
	struct sockaddr_in servaddr;	/* server address */
	/* get a tcp/ip socket */
	/* We do this as we did it for the server */
	/* request the Internet address protocol */
	/* and a reliable 2-way byte stream */
	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("cannot create socket");
		return 0;
	}
	/* bind to an arbitrary return address */
	/* because this is the client side, we don't care about the */
	/* address since no application will connect here  --- */
	/* INADDR_ANY is the IP address and 0 is the socket */
	/* htonl converts a long integer (e.g. address) to a network */
	/* representation (agreed-upon byte ordering */
	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(0);
	// bind() the socket to struct sockaddr_in myaddr information
	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("bind failed");
		return 0;
	}
	/* this part is for debugging only - get the port # that the operating */
	/* system allocated for us. */
        alen = sizeof(myaddr);
        if (getsockname(fd, (struct sockaddr *)&myaddr, &alen) < 0) {
                perror("getsockname failed");
                return 0;
        }
	printf("local port number = %d\n", ntohs(myaddr.sin_port));

	/* fill in the server's address and data */
	/* htons() converts a short integer to a network representation */

	memset((char*)&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);

	/* look up the address of the server given its name */
	hp = gethostbyname(host);
	if (!hp) {
		fprintf(stderr, "could not obtain address of %s\n", host);
		return 0;
	}

	/* put the host's address into the server address structure */
	memcpy((void *)&servaddr.sin_addr, hp->h_addr_list[0], hp->h_length);

	/* connect to server */
	if (connect(fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		perror("connect failed");
		return 0;
	}
	return 1;
}

/* disconnect from the service */
void disconn(void)
{
	printf("disconn()\n");
	shutdown(fd, 2);    /* 2 means future sends & receives are disallowed */
}

int main(int argc, char **argv)
{
	// setting up the host IP address and port to create the socket()
	int port = SERVICE_PORT;	
	char *host = "localhost";	/* default: this host */
	// print the selected IP address and port before creating the socket()
	printf("connecting to %s, port %d\n", host, port);
	// create the socket()
	if (!conn(host, port))    /* connect */
		exit(1);   /* something went wrong */

	disconn();    /* disconnect */
	return 0;
}

