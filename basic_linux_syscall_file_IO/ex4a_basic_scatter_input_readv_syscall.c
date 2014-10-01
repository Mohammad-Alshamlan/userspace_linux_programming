/*
 * source: page 95 (121 in pdf) in linux system programming 2nd edition
 * Also, $ man readv
 */
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/uio.h>

int main()
{
	char foo[47], bar[50], baz[47];
	struct iovec iov[3];
	ssize_t nr;
	int fd, i;
	//
	fd = open("ex4a_text_example.txt", O_RDONLY);
	if (fd == -1) {
		perror("open");
		return 1;
	}
	/* set up our iovec structures */
	iov[0].iov_base = foo;
	iov[0].iov_len = sizeof (foo);
	iov[1].iov_base = bar;
	iov[1].iov_len = sizeof (bar);
	iov[2].iov_base = baz;
	iov[2].iov_len = sizeof (baz);
	
	/* read into the structures with a single call */
	nr = readv (fd, iov, sizeof(iov)/sizeof(iov[0])); // 3 is because we define three iov variables
	if ( nr== -1){
		perror("readv");
		return 1;
	}
	
	for (i=0 ; i < sizeof(iov)/sizeof(iov[0]) ; i++)
		printf("%d: %s\n", i, (char *) iov[i].iov_base);
	if(close(fd)){
		perror("close");
		return 1;
	}
	return 0;
}
