/*
 * we want to do a binary search in a file with using lseek() 
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

// get the last word that has been captured from lseek(), and also change the lseek() offset to point to that word
char *get_word(int fd, char *word, off_t len)
{
	int needed_offset_shift = 2;
	// cleanup the word -- because it is reusable!!
	memset(word, 0, MAX_WORD_LENGTH);
	// reading the file
	size_t max_read = ((size_t) MAX_WORD_LENGTH < (size_t) len)? (size_t) MAX_WORD_LENGTH -1 : (size_t) len;
	read (fd, word, max_read);
	// insert null termination at the end of 'word' just in case
	word[MAX_WORD_LENGTH -1]='\0';
	// append utill you get a newline
	int i, count=2; 
	for (i=strlen(word); (i != 0) && (count != 0); i--)
		if(word[i]=='\n')
			count--; 
	// shift the offset to the selected word address
	off_t current_pos= lseek( fd, 0L, SEEK_CUR ); 
	if( lseek(fd, (off_t) current_pos -  i + needed_offset_shift, SEEK_SET) == -1 ) {
		perror("I can't do SEEK_SET!!\n");
		exit(EXIT_FAILURE);		
	}
	// now, &word[i + needed_offset_shift ] starts at the bigging of the last word, but it also has garbage in the end such as: '\n', '\r', or part of the next not well-formed word
	// we know that, before the new word starts, there are '\n' and '\r' before it, so we can nulify them!!
	int j;
	char *clean_word= &word[i + needed_offset_shift ];
	for(j=0; clean_word[j] != '\0'; j++)
		if((clean_word[j]=='\n') || (clean_word[j]=='\r'))
			clean_word[j]='\0';
	// return the word
	return clean_word;	// I'm still not sure why '+2' works, and '+1' gives a space in the beginning 
}

// in this point, we have a buffer that has the keyword that we are looking for, or simply the keyword isn't in the file
// we know the last word in the buffer, and also we know that it is well-formed word. However, the first word may not be
// a well-formed word!!  
char *short_binary_search_comparator(char *keyword, char *word, char *pword_middle)
{
	// convert every '\r' and '\n' to '\0'
	int i, len=strlen(word);
	for( i=0; i<len; i++)
		if((word[i]=='\n') || (word[i]=='\r'))
			word[i]='\0';
	// let create a pointer to each word, and then compare!!
	char *pstr=NULL;
	for(i=1; i<len; i++)
		if((i -1 == 0) || ((word[i-1]=='\0') && (word[i] != '\0') ) ){
			pstr=&word[i];
			if(strcmp(keyword, pstr) == 0)
				return pstr;
		}
	return NULL;
}

// there are three scenarios that we need to take into consideration:
// [1] insofar, we have the kayword in the word buffer
// [2] we have the keyword in the word buffer, but it is not well-formed. Missing part of it
// [3] we don't have the word
char *short_binary_search(int fd, char *keyword, char *word, char *pword_middle, off_t len)
{
	// if the keyword that we are looking for is well-formed in word buffer, that is great. However, sometime just part of the word is there!!! 
	char *cmp=short_binary_search_comparator(keyword, word, pword_middle);
	if(cmp != NULL)
		return cmp;
	else {
		// maybe the word is not well-formed or doesn't exist. So, let get a new word buffer
		off_t current_off = lseek( fd, 0L, SEEK_CUR );
		// make sure we don't get negative offset -- negative offset means the keyword doesn't exist
		if((current_off - MAX_WORD_LENGTH) < 0)
			return NULL;
		// set lseek() more to the left
		else if( lseek(fd, current_off - MAX_WORD_LENGTH  , SEEK_SET) == -1 ) {
			perror("short_binary_search(): I can't do SEEK_SET!!\n");
			exit(EXIT_FAILURE);		
		}
		get_word(fd, word, len);
		return short_binary_search_comparator(keyword, word, pword_middle);
	}
	return NULL;
}

// searching for the keyword
char *binary_search(int fd, char *keyword, off_t len, char *word)
{
	// make the word reusable!!
	char *pword= get_word(fd, word, len);
	// set binary search variables
	off_t L=0, R=lseek( fd, 0L, SEEK_CUR ), M=0;
	char *pword_middle=NULL, previous_pword_middle[MAX_WORD_LENGTH];
	memset(previous_pword_middle, 0, MAX_WORD_LENGTH);	
	// search for the selected word
	if( strcmp(keyword, pword) <= 0 ) {
		while(L<R){
			M=(L+R-1)/2;
			// set lseek() into the middle
			if( lseek(fd, M, SEEK_SET) == -1 ) {
				perror("binary_search(): I can't do SEEK_SET!!\n");
				exit(EXIT_FAILURE);		
			}	
			pword_middle=get_word(fd, word, len);
			// make M to be the offset of a biginning of a word, and not a random offset position
			M=lseek( fd, 0L, SEEK_CUR );
			if((strcmp(keyword, pword_middle)== 0) && (strlen(keyword) == strlen(pword_middle)))
				return pword_middle;
			else if(strcmp(keyword, pword_middle) < 0){
				if (strcmp(pword_middle, previous_pword_middle) != 0)
					R=M;
				else {
					// in this case, that means that the 'keyword' is part of 'word'
					// we don't need to iterate again!! We simply can fix it here
					// Note, this method is used for optimization, so if there is a better appraoch, then replace this!!!
					return short_binary_search(fd, keyword, word, pword_middle, len);
				}
			} else if (strcmp(keyword, pword_middle) > 0)
				L=M+strlen(pword_middle); // adding a word here is important because if doesn't it will be infint loop!! 
			// copy the current word
			strcpy(previous_pword_middle, pword_middle);
		}
	}
	return NULL;
}

//
void lseek_file (const char *filename, char *keyword, char *word)
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
	// set the file position to point to the last word if possible -- this is a rough estimate which will be fixed accordingly later!!!
	if( lseek(fd, len - MAX_WORD_LENGTH, SEEK_SET) == -1 ) {
		perror("I can't do SEEK_SET!!\n");
		exit(EXIT_FAILURE);		
	}	
	// look for the word
	char *pword = binary_search(fd, keyword, len, word); 
	if(pword)
		printf("found: %s\n", pword);
	else
		printf("couldn't find %s!!\n", keyword);
	// done, with the file
	close (fd);
}

int main(int argc, char *argv[])
{
	if(argc < 3){
		perror("you are missing command-line arguments\nPlease, do the following\n\t$ <program> <filename> <keyword>\n");
		exit(EXIT_FAILURE);
	}
	// assuming that there isn't a word that larger than MAX_WORD_LENGTH value
  	char word[MAX_WORD_LENGTH];
	// pass the filename into our function
	// argv[1] == <filename>
	// argv[2] == <keyword>
	lseek_file(argv[1], argv[2], word);
	// done!!
	return 0;	
}
