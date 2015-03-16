/*
 * source: the manpage for getaddrinfo()
 *	(bash) $ man getaddrinfo
 * 
 * Objective: gethostbyname() got deprecated by getaddrinfo() due to gethostbyname() bad support for ipv6
 *
 * to-do-list
 *	[1] use designated initializer for struct addrinfo
 */

#include <sys/types.h>		/* ???  why including it, unistd.h will take care of system types!! */
#include <sys/socket.h>
#include <netdb.h>		/* ???  why including it, sys/socket.h will take care of system types!! */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifndef BUF_SIZE
#define BUF_SIZE 500
#endif 

int main(int argc, char *argv[])
{
	// ??? why three of them!!
	struct addrinfo hints;
	struct addrinfo *result, *rp;
	// 	
	int sfd, s;
	// what the heck is "struct sockaddr_storage" ???
	struct sockaddr_storage peer_addr;
	// 
	socklen_t peer_addr_len;
	ssize_t nread;
	char buf[BUF_SIZE];
	// check command line arguments
	if (argc != 2) {
		fprintf(stderr, "Usage: %s port\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	// define hints structure
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	hints.ai_protocol = 0;          /* Any protocol */
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	// use argv[1] for port!!
	s = getaddrinfo(NULL, argv[1], &hints, &result);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}

   /* getaddrinfo() returns a list of address structures.
       Try each address until we successfully bind(2).
       If socket(2) (or bind(2)) fails, we (close the socket
       and) try the next address. */

   for (rp = result; rp != NULL; rp = rp->ai_next) {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sfd == -1)
            continue;

       if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;                  /* Success */

       close(sfd);
    }

   if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not bind\n");
        exit(EXIT_FAILURE);
    }

   freeaddrinfo(result);           /* No longer needed */

   /* Read datagrams and echo them back to sender */

   for (;;) {
        peer_addr_len = sizeof(struct sockaddr_storage);
        nread = recvfrom(sfd, buf, BUF_SIZE, 0,
                (struct sockaddr *) &peer_addr, &peer_addr_len);
        if (nread == -1)
            continue;               /* Ignore failed request */

       char host[NI_MAXHOST], service[NI_MAXSERV];

       s = getnameinfo((struct sockaddr *) &peer_addr,
                        peer_addr_len, host, NI_MAXHOST,
                        service, NI_MAXSERV, NI_NUMERICSERV);
       if (s == 0)
            printf("Received %ld bytes from %s:%s\n",
                    (long) nread, host, service);
        else
            fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));

       if (sendto(sfd, buf, nread, 0,
                    (struct sockaddr *) &peer_addr,
                    peer_addr_len) != nread)
            fprintf(stderr, "Error sending response\n");
    }
}

