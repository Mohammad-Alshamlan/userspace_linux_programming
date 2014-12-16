/*
 * objectives:
 *	[1] write down TCP daytime client
 *	[2] using getaddrinfo() is better than gethostbyname() because getaddrinfo() supports ip6 much better
 *	[3] let the address family to be left unspecified so that both IPv4 and IPv6 addresses can be returnrf. In principle, 
 *	    you can receive results for other address families too: you can either treat this as a feature, or filter out any unwanted
 *	    results after the call to getaddrinfo()
 *	[4] The AI_PASSIVE flag for struct addrinfo has not been set because the result is intended for use as a remote address. 
 *	    Its absence causes the IP address to default to the loopback address (as opposed to the wildcard address).
 *	[5] The AI_ADDRCONFIG flag for struct addrinfo has been set so that IPv6 results will only be returned if the server has an 
 *	    IPv6 address, and similarly for IPv4.
 *	[6] using STDOUT_FILENO with write() (which came from unistd.h) rather than using stdout (from stdio.h) write(strout, , )
 *	[7] simulating the TCP daytime server as follows:
 *		(bash) $ sudo ncat -l 13 --send-only --exec "/bin/date"
 *
 * Notes:
 *	[1] When iterating through a list of addresses returned by getaddrinfo it is potentially necessary to create a separate socket 
 *	    for each, because the addresses will not necessarily be members of the same address family or use the same protocol.
 *	[2] I used root premission for:
 *		(bash) $ sudo ncat -l 13 --send-only --exec "/bin/date"
 *
 *	    because this what I got when I ran it as regular user:
 *	    	alshamlan@alshamlan-K55A:~$ ncat -l 13 --send-only --exec "/bin/date" 
 *		Ncat: bind to :::13: Permission denied. QUITTING.
 *		alshamlan@alshamlan-K55A:~$
 */ 

#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<sys/socket.h>
#include<netinet/in.h>

// adding stdio.h because I'm using perror()
#include<stdio.h>

int main(int argc, char *argv[])
{
	// defining needed var's to connect to TCP daytime server
	const char *hostname=0;	// 0 == localhost
	const char *portname="daytime";
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;
	hints.ai_protocol=0;
	hints.ai_flags=AI_ADDRCONFIG;
	/* 
	 * The res argument is used to return a linked list of addrinfo structures containing the address or addresses that were found. 
	 * If multiple records are returned then the recommended behaviour (from RFC 1123) is to try each address in turn, stopping 
	 * when a connection is successfully established. When doing this you may wish to limit the number of addresses tried and/or 
	 * allow connection attempts to overlap, in order to prevent the cumulative timeout period from becoming excessive. 
	 */
	struct addrinfo *res=0;
	int rc = getaddrinfo(hostname, portname, &hints, &res);
	if (rc){
		perror("getaddrinfo() error!!");
		return 1;
	}
	// create a socket
	int fd=socket(res->ai_family,res->ai_socktype,res->ai_protocol);
	if (fd == -1){
		perror("socket() failed!!");
		return 1;
	}
	// Connect the socket to the remote address.
	/* 
	 * By default the connect function blocks until the initial TCP handshake has been completed and the socket is ready for use, 
	 * or alternatively, until the connection attempt fails. Some types of connection failure are reported very quickly, whereas 
	 * others can only be detected by means of a timeout. In the latter case connect may block for several minutes.
	 */
	rc = connect(fd,res->ai_addr,res->ai_addrlen);
	if (rc){
		perror("connect() failed!!");
		return 1;
	}
	/* 
	 * If the remote address was constructed using getaddrinfo then the memory occupied by the address list can now be released.
	 */
	freeaddrinfo(res);
	// The socket descriptor is now ready for use. 
	// Here is an example of how it might be utilised to implement a Daytime Protocol client:
	char buffer[256];
	for (;;) {
	    ssize_t count=read(fd,buffer,sizeof(buffer));
	    if (count<0) {
		if (errno!=EINTR){
			perror("read() failed!!");
			return 1;
		} 
	    } else if (count==0) {
		break;
	    } else {
		write(STDOUT_FILENO,buffer,count);
	    }
	}
	close(fd);
	// done!!
	return 0;
} 
