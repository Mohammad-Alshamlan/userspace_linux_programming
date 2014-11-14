#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 512

int main()
{
	// opening src and dest
	int src = open("ex5f_double_linkedlist", O_RDONLY);
	if (src == -1){
		perror("I can't open the src file!!\n");
		exit(EXIT_FAILURE);		
	}
	gzFile dest = gzopen("ex5f_double_linkedlist.gz", "wb");
	if (!dest){
		perror("I can't open the dest file!!\n");
		exit(EXIT_FAILURE);		
	}
	// get the size of the src file, note we can use lseek instead!!
	struct stat file_info;	
	fstat (src, &file_info);
	size_t len= file_info.st_size;
	// copy from src to dest
	char buff[len];
	memset(buff, 0, len);
	read(src, buff, len);
	gzwrite(dest, buff, len);
	// I need to flush the stream into the disk!!
	gzflush(dest,  Z_FULL_FLUSH);
	// done
	gzclose(dest);
	close(src);
	return 0;
}
