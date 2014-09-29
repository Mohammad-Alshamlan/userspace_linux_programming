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
#define NUMBER_OF_WORDS 2
#define MAX_WORD_LENGTH ((NUMBER_OF_WORDS * 32) + 0) // 0 because you unlikely would have 32-word-length back-to-back

/*
int *binary_search(int val, int *list, size_t len)
{
	int L=0, R=(int)len, M;
	if(val <= list[len -1]){
		while(L<R){
			M=(L+R-1)/2;
			if(val==list[M])
				return &list[M];
			else if(val < list[M])
				R=M;
			else if (val > list[M]) 
				L=M+1; // adding one here is important because if doesn't it will be infint loop!! 
		}
	}
	return NULL;
}
*/

// get a word
char *get_word(int fd, char *word, off_t len)
{
	// cleanup the word -- because it is reusable!!
	memset(word, 0, MAX_WORD_LENGTH);
	// reading the file
	size_t max_read = ((size_t) MAX_WORD_LENGTH < (size_t) len)? (size_t) MAX_WORD_LENGTH -1 : (size_t) len;
	read (fd, word, max_read);
	// append utill you get a newline
	int count, i; 
	// count == 2 because we are looking for the last two newline 
	for (i=strlen(word), count=1; (count != 0) && (i != 0); i--)
		if(word[i]=='\n')
			count--; 
	// return the word
	return &word[i + 2 ];	// I'm still not sure why '+2' works, and '+1' gives a space in the beginning 

}

// searching for the keyword
int binary_search(int fd, char *keyword, off_t len)
{
	off_t L=0, R=len, M;
	// assuming that there isn't a word that larger than MAX_WORD_LENGTH value
  	char word[MAX_WORD_LENGTH];
	// make the word reusable!!
	char *pword= get_word(fd, word, len);
	if( strcmp(keyword, pword) <= 0 ) {
		printf("last word: %s\n", pword);
	
	}
	return 0;
}

void lseek_file (const char *filename, char *keyword)
{
	int fd;
	/* Open the file.  */
	fd = open (filename, O_RDONLY);
	if (fd == -1){
		perror("I can't open the file!!\n");
		exit(EXIT_FAILURE);		
	}
	// set to the EOF (end of file) with lseek(), which is the lenght of the file
	off_t len;
	len = lseek(fd, 0, SEEK_END);
	if(len == (off_t) -1){
		perror("I can't do SEEK_END!!\n");
		exit(EXIT_FAILURE);		
	}
	// set the file position to point to the last word if possible
	if( lseek(fd, len - MAX_WORD_LENGTH, SEEK_SET) == -1 ) {
		perror("I can't do SEEK_SET!!\n");
		exit(EXIT_FAILURE);		
	}	
	// look for the word
	int search_result = binary_search(fd, keyword, len); 
	
	
	/*
	// get the midpoint
	midpoint= len/2;
	// set the file position to midpoint
	if( lseek(fd, midpoint, SEEK_SET) == -1 ) {
		perror("I can't do SEEK_SET!!\n");
		exit(EXIT_FAILURE);		
	}
	*/
	
	/* Finish up.  */
	close (fd);
}

int main(int argc, char *argv[])
{
	if(argc < 3){
		perror("you are missing command-line arguments\nPlease, do the following\n\t$ <program> <filename> <keyword>\n");
		exit(EXIT_FAILURE);
	}
	// pass the filename into our function
	// argv[1] == <filename>
	// argv[2] == <keyword>
	lseek_file(argv[1], argv[2]);
	// done!!
	return 0;	
}
