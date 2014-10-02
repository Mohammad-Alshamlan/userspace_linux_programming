/*  <incomplete>!!!
 * the idea is to create concatenated positional words for a large file
 * [1] we sill assume that the biggest word possible is 32 letters, and there is no way that we would have bigger than 32
 * [2] 
 */
 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

// assuming each word length at most 32, and there isn't a word larger than that
#define NUMBER_OF_WORDS 2
#define MAX_WORD_LENGTH ((NUMBER_OF_WORDS * 32) + 0) // 0 because you unlikely would have 32-word-length back-to-back


//
typedef struct node {
	size_t len;
	off_t offset;
	struct node *next;
} node_t;

// creating a stack
typedef struct stack {
	node_t *top;
} stack_t;

void push(stack_t *s, size_t len, off_t offset)
{
	// creating and defining a new node
	node_t *new=(node_t *) malloc (sizeof(node_t));
	new->len=len;
	new->offset=offset;
	// mapping the new node into the stack -- FIFO 
	new->next=s->top;
	s->top=new;
}

void pop(stack_t *s)
{
	node_t *remove=s->top;
	s->top=s->top->next;
	free(remove);
}


int main()
{
	FILE *fp =fopen("0_large_example_list.txt","r"); 
	char str[MAX_WORD_LENGTH];
	size_t max_len=0, len;
	long offset_previous=0;
	int i;
	// creating a stack to hold the metadata
	stack_t *s = (stack_t *) malloc (sizeof(stack_t));
	s->top=NULL;
	// 
	while((fgets(str,MAX_WORD_LENGTH,fp)) != NULL){
		// cleanup the word form '\n' and '\r'
		for (i=0; str[i] != '\0' ; i++)
			if((str[i]=='\n') || (str[i]=='\r'))
				str[i]='\0';
		// get the length
		len = strlen(str);
		// keep a record for the largest
		max_len = (max_len > len)? max_len : len;
		// get the offset
		//offset_previous);
		// debug
		//printf("word=%s\tlen=%zu\toffset=%ld\n", str, max_len, offset);
		// push it into the stack
		push(s, len, offset_previous);
		offset_previous=ftell(fp);
	}
	printf("largest word is %d\n", (int) max_len);
	// let print the biggest words that we found
	node_t *j=NULL;
	for(j=s->top; j!=NULL; j=j->next)
		if(j->len == max_len){
			// let get this word
			// set the offset to this word
			fseek(fp, j->offset, SEEK_SET );
			fgets(str,MAX_WORD_LENGTH,fp);
			// print the word
			printf("len=%d\tword=%s", (int) j->len, str);
		}
	// getting the file descriptor from a stream, and using lseek() instead of fseek()!!
	int fd = fileno (fp);
	char buff[max_len+1];
	for(j=s->top; j!=NULL; j=j->next)
		if(j->len == max_len){
			// let get this word
			// set the offset to this word
			lseek(fd, (off_t) j->offset, SEEK_SET );
			read (fd, buff, max_len+1);
			buff[max_len]='\0';
			printf("buff:%s\n", buff);
		}
	 
 	// done
 	stack_t *done;
	for(done=s; done->top != NULL ; /*no need!! pop() does it*/)
		pop(done);
	free(s);	
 	fclose(fp);
        return 0;

}
