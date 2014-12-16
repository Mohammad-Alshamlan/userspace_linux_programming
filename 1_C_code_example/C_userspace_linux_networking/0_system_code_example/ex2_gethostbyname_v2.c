/*
 * source: https://www.cs.rutgers.edu/~pxk/417/notes/sockets/index.html
 *
 * This code prints all the IP of the host after getting from gethostbyname()
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>

/* paddr: print the IP address in a standard decimal dotted format */
void paddr(unsigned char *a)
{
        // exactly convering ASCII char into an integer value. For example, zero ASCII == 48 integer value, and not zero integer!! 
        printf("%d.%d.%d.%d\n", a[0], a[1], a[2], a[3]);
}

int main(int argc, char *argv[]) {
        // setting up local variables
        struct hostent *hp;
        char *host = "google.com";
	// configuring struct hostent *hp
        hp = gethostbyname(host);
        // error check
        if (!hp) {
                herror("could not obtain IP address from the given hostname!!");
                return 1;
        }
        // printing out all collected IP addresses
        while( *hp->h_addr_list != 0)
                paddr((unsigned char*) *(hp->h_addr_list++));
        // done!! Notice, we haven't used socket(), so there isn't a need to free anything!! Simply exit(0) or return 0
        exit(0);
}
