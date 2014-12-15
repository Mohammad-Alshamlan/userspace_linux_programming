/*
 * The idea is to copy a binary file such as a picture. 
 * Note, we can't use open(), read(), or write() in binary files
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


