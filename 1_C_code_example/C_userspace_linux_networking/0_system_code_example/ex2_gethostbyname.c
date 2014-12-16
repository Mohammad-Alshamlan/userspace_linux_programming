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
void
paddr(unsigned char *a)
{
        // exactly convering ASCII char into an integer value. For example, zero ASCII == 48 integer value, and not zero integer!! 
        printf("%d.%d.%d.%d\n", a[0], a[1], a[2], a[3]);
}

int main(int argc, char **argv) {
        // setting up local variables
        struct hostent *hp;
        char *host = "google.com";
        int i;
	// configuring struct hostent *hp
        hp = gethostbyname(host);
        // error check
        if (!hp) {
                fprintf(stderr, "could not obtain address of %s\n", host);
                return 0;
        }
        // printing out all collected IP addresses
        for (i=0; hp->h_addr_list[i] != 0; i++)
                paddr((unsigned char*) hp->h_addr_list[i]);
        // done!! Notice, we haven't used socket(), so there isn't a need to free anything!! Simply exit(0) or return 0
        exit(0);
}
