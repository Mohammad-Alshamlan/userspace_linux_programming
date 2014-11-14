// THIS IS A DEPRECATED METHOD OF GETTING HOST NAMES
// use getaddrinfo() instead!
/*
 * Example 1: 
 *	(bash) $ hostname
 *	alshamlan-Precision-M6700 
 *
 *	(bash) $ ./get_hostname alshamlan-Precision-M6700
 *	Official name is: alshamlan-Precision-M6700
 *	IP addresses: 127.0.1.1 
 *   
 * Example 2: 
 *	(bash) $ ./get_hostname `hostname`
 *	Official name is: alshamlan-Precision-M6700
 *	IP addresses: 127.0.1.1 
 * 
 * Example 3: 
 *	(bash) $ ./get_hostname 127.0.0.1
 *	Official name is: 127.0.0.1
 *	IP addresses: 127.0.1.1 
 * 
 * Example 4, using a hostname for my another machine that is connected to the network:
 *	(bash) $ ./get_hostname alshamlan-OptiPlex-980
 *	Official name is: alshamlan-OptiPlex-980.pace.internal
 *	IP addresses: 136.170.210.98 
 */

#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int i;
    struct hostent *he;
    struct in_addr **addr_list;

    if (argc != 2) {
        fprintf(stderr,"usage: ghbn hostname\n");
        return 1;
    }

    if ((he = gethostbyname(argv[1])) == NULL) {  // get the host info
        herror("gethostbyname");
        return 2;
    }

    // print information about this host:
    printf("Official name is: %s\n", he->h_name);
    printf("    IP addresses: ");
    addr_list = (struct in_addr **)he->h_addr_list;
    for(i = 0; addr_list[i] != NULL; i++) {
        printf("%s ", inet_ntoa(*addr_list[i]));
    }
    printf("\n");

    return 0;
}
