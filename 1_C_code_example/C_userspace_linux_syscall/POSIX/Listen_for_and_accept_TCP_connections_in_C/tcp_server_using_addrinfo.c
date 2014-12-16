/*
objectives:
[1] The local IP address should normally default to either the the wildcard address or the loopback address, but like the port number it is good practice to make it configurable. When a service is bound to a particular IP address it will only accept connections directed to that address, whereas when bound to the wildcard address it will accept connections to any local address. Binding to the loopback address has the effect of prohibiting connections from other machines.
[2] For most purposes the best way to construct the socket address is by calling getaddrinfo. This takes a string containing the IP address and a string containing the port number, and converts them into a sockaddr_in or a sockaddr_in6 as appropriate. It is also able to resolve hostnames and service names:
[3] using SO_REUSEADDR, SO_REUSEADDR should be routinely set for TCP server sockets in order to allow the network service to be restarted when there are connections in the ESTABLISHED or TIME-WAIT state:
[4] using SOMAXCONN as listen() backlog, The second argument is the backlog of outstanding connections that the operating system should queue while they are waiting to be accepted by the server process. It is only a hint: most implementations take some account of the value requested, but you should not make any assumptions. A value of SOMAXCONN indicates that the maximum permissible queue length should be selected.
[5] Connections are accepted by the server process by repeatedly calling the accept function. Each time this is done a new socket descriptor is returned to act as an endpoint for the newly established connection. If no connections are available then the function blocks. The process of handling a connection should preferably not interfere with the acceptance or handling of other connections. One way to ensure this is to spawn a new child process for each connection:


Notes:
[1]


to-do-list:
[1] know the server IP address
[2] try to compile the code because I haven't tried it yet
*/

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Functionality that is specific to the network service is represented here by the function handle_session. As a simple example, here is an implementation of the Daytime Protocol:
void handle_session(int session_fd) {
    time_t now=time(0);
    char buffer[80];
    size_t length=strftime(buffer,sizeof(buffer),"%a %b %d %T %Y\r\n",localtime(&now));
    if (length==0) {
        snprintf(buffer,sizeof(buffer),"Error: buffer overflow\r\n");
    }

    size_t index=0;
    while (index<length) {
        ssize_t count=write(session_fd,buffer+index,length-index);
        if (count<0) {
            if (errno==EINTR) continue;
            die("failed to write to socket (errno=%d)",errno);
        } else {
            index+=count;
        }
    }
}

int main (int argc, char *argv[])
{
const char* hostname=0; /* wildcard */
const char* portname="daytime";
struct addrinfo hints;
memset(&hints,0,sizeof(hints));
hints.ai_family=AF_UNSPEC;
hints.ai_socktype=SOCK_STREAM;
hints.ai_protocol=0;
// [1] The AI_PASSIVE flag has been set because the address is intended for binding to a server socket. It causes the IP address to default to the wildcard address as opposed to the loopback address.
// [2] The AI_ADDRCONFIG flag has been set so that IPv6 results will only be returned if the server has an IPv6 address, and similarly for IPv4.
hints.ai_flags=AI_PASSIVE|AI_ADDRCONFIG;
struct addrinfo* res=0;
int err=getaddrinfo(hostname,portname,&hints,&res);
if (err!=0) {
    die("failed to resolve local socket address (err=%d)",err);
}
// create socket
int server_fd=socket(res->ai_family,res->ai_socktype,res->ai_protocol);
if (server_fd==-1) {
    die("%s",strerror(errno));
}
// Set the SO_REUSEADDR socket option
int reuseaddr=1;
if (setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&reuseaddr,sizeof(reuseaddr))==-1) {
    die("%s",strerror(errno));
}
// bind()
if (bind(server_fd,res->ai_addr,res->ai_addrlen)==-1) {
    die("%s",strerror(errno));
}
//If the local address was constructed using getaddrinfo then the memory occupied by the address list can now be released:
freeaddrinfo(res);
// (If the address list has been searched or filtered then take care that it is the head of the list that is released, not the address that you have chosen to use.)

// lsiten()
if (listen(server_fd,SOMAXCONN)) {
    die("failed to listen for connections (errno=%d)",errno);
}
// accept() and making sure each accept() is a process
// Note: The parent process should close the descriptor for each connected socket once the corresponding child process has been spawned. There are two reasons for doing this: to prevent the descriptors from accumulating, and to prevent the connection from being held open by the parent after it has been closed by the child. Similarly, the child process should close any file or socket descriptors inherited from the parent that it does not need access to. This will certainly include the descriptor for the server socket, but you should consider whether there are any others.
for (;;) {
    int session_fd=accept(server_fd,0,0);
    if (session_fd==-1) {
        if (errno==EINTR) continue;
        die("failed to accept connection (errno=%d)",errno);
    }
    pid_t pid=fork();
    if (pid==-1) {
        die("failed to create child process (errno=%d)",errno);
    } else if (pid==0) {
        close(server_fd);
        handle_session(session_fd);
        close(session_fd);
        _exit(0);
    } else {
        close(session_fd);
    }
}


}
