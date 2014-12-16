/*
 * The idea is to copy a binary file such as a picture. 
 * Note, we can't use open(), read(), or write() in binary files -- I found out this claim is false!!
 * 
 * to send the image through socket programming, you need to be aware of the following:
 *	[1] You need to open the file in binary mode ("rb" for reading, "wb" for writing), not the default text mode. On Windows (and any other systems which do line ending translation), the 
 *	    stdio library converts LFs (bytes 0x0A) into CRLF pairs (the two bytes 0x0D 0x0A) when writing, and it does the inverse translation when reading. For non-text data like JPEG files, 
 *	    this corrupts the data.
 *
 *	[2] There's no need to be sending your "handshake" bytes after each send. TCP/IP already handles acknowledgements/resends/flow control/etc. You can assume that as long as send()/write() 
 *	    returns a positive value, then that many bytes were received by the other peer.
 *
 *	[3] send()/write() may not send all of the data you ask it to—they may do a partial send. If that happens, you need to keep trying to send the rest of the buffer in a loop.
 *
 *	[4] sizeof(char) is guaranteed to be 1 by the C language standard, there's rarely a need to say sizeof(char) when instead your code will be much clearer without it
 *
 *	[5] In the client code, there's no need to use that ioctl to determine how much data can be read without blocking because you're just looping again—your code will spin at 100% CPU while 
 *	    there's no data available. Just let the read() call block. If you're running this code on a laptop, your battery will thank you.
 *
 *	[6] Likewise, the client will almost definitely be getting partial reads, you're not going to receive the whole file in a single call. You need to write out whatever data you get, then 
 *	    loop and receive again.
 *
 *	[7] When you send the image size over the socket at the start, you might get a different value on the client if the two systems are not of the same endianness. In order to make your
 *	    code bulletproof, you need to convert the data to network order (big-endian) when sending it, then convert it back to host (native) order after receiving it. You can use the 
 *	    ntohl(3) and htonl(3) functions to do these conversions for 4-byte values.
 */

#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifndef DEST_FILE
#define DEST_FILE "dest_file.jpeg"
#endif

#ifndef BUFF_SIZE
#define BUFF_SIZE 512
#endif

int main(int argc, char *argv[])
{
	// check if we have the right number of aruments
	if(argc < 2){
		fprintf(stderr, "you're missing the file name. Please, run it as follows:\n\t(bash) $ %s <filename>\n", argv[0]);
		return 1;
	}
	// open the source file, and make sure that you have opened the file


    // BUFSIZE default is 8192 bytes
    // BUFSIZE of 1 means one chareter at time
    // good values should fit to blocksize, like 1024 or 4096
    // higher values reduce number of system calls
    // size_t BUFFER_SIZE = 4096;

    char buf[BUFF_SIZE];
    size_t size;

    FILE* source = fopen(argv[1], "rb");
    FILE* dest = fopen(DEST_FILE, "wb");

    // clean and more secure
    // feof(FILE* stream) returns non-zero if the end of file indicator for stream is set

    while ((size = fread(buf, 1, BUFF_SIZE, source))) {
        fwrite(buf, 1, size, dest);
    }

    fclose(source);
    fclose(dest);
	return 0;
}


