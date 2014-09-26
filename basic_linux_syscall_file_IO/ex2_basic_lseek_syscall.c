/*
 * we want to print three words in a middle of a file!!
 */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

// assuming each word length at most 32, and there isn't a word larger than that
#define NUMBER_OF_WORDS 3
#define MAX_WORD_LENGTH ((NUMBER_OF_WORDS * 32)) // unlikely you would have 32 word length back-to-back

void lseek_file (const char* filename)
{
	int fd;
  	// assuming that there isn't a word that larger than MAX_SIZE value
  	char buffer[MAX_WORD_LENGTH];
  	memset(buffer, 0, MAX_WORD_LENGTH);
	/* Open the file.  */
	fd = open (filename, O_RDONLY);
	if (fd == -1){
		perror("I can't open the file!!\n");
		exit(EXIT_FAILURE);		
	}
	// set to the EOF (end of file) with lseek(), which is the lenght of the file
	off_t len, midpoint;
	len = lseek(fd, 0, SEEK_END);
	if(len == (off_t) -1){
		perror("I can't do SEEK_END!!\n");
		exit(EXIT_FAILURE);		
	}
	// get the midpoint
	midpoint= len/2;
	// set the file position to midpoint
	if( lseek(fd, midpoint, SEEK_SET) == -1 ) {
		perror("I can't do SEEK_SET!!\n");
		exit(EXIT_FAILURE);		
	}
	// reading the file
	size_t max_read = ((size_t) MAX_WORD_LENGTH < (size_t) len)? (size_t) MAX_WORD_LENGTH -1 : (size_t) len;
	read (fd, buffer, max_read);
	buffer[max_read + 1]='\0';
	// append utill you get a newline
	int pos=0, i; 
	while(buffer[pos++]!='\n') 
		/*nothing*/ ;
	// convert all newlines into null-termination
	for(i=pos; buffer[i] != '\0' ; i++)
		if(buffer[i]=='\n')
			buffer[i]='\0';
	// print the selected number of words
	for(i=0; i < NUMBER_OF_WORDS ; i++)
		pos += printf("%s\n", &buffer[pos]);	
	/* Finish up.  */
	close (fd);
}

int main(int argc, char *argv[])
{
	if(argc < 2){
		perror("you are missing command-line argument\nPlease, include the file name\n");
		exit(EXIT_FAILURE);
	}
	// pass the filename into our function
	lseek_file(argv[1]);
	// done!!
	return 0;	
}
