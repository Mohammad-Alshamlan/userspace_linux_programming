/*
 * The idea is to copy a binary file such as a picture. 
 * from two file descriptors
 */

#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

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
	// open the source file, and make sure it is opened correctly
	int fd_src = open(argv[1], O_RDONLY);
	if(fd_src == -1){
		perror("opening fd_src failed!!");
		return 1;
	}
	// open the destination file (or create it), and make sure it is opened correctly
	int fd_dest = open(DEST_FILE, O_WRONLY | O_CREAT);
	if(fd_dest == -1){
		perror("opening fd_src failed!!");
		return 1;
	}
	// copy from the source file to destination file
	char buffer[BUFF_SIZE];
	memset(buffer, 0, sizeof(buffer));
	size_t read_len = 0, write_len=0; 
	while((read_len = read(fd_src, buffer, BUFF_SIZE)) > 0){
		write_len = write(fd_dest, buffer, read_len);
		// check if it isn't partial write
		if(read_len != write_len){
			perror("partail write!!");
			return 1;
		}
	}
	// done
	close(fd_src);
	close(fd_dest);
	return 0;
}
	

