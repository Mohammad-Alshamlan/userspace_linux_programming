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

void create_the_stack(FILE *fp, stack_t *s, size_t *max_len, size_t *min_len)
{
	char str[MAX_WORD_LENGTH];
	size_t len;
	long offset_previous=0;
	int i;
	// 
	while((fgets(str,MAX_WORD_LENGTH,fp)) != NULL){
		// cleanup the word form '\n' and '\r'
		for (i=0; str[i] != '\0' ; i++)
			if((str[i]=='\n') || (str[i]=='\r'))
				str[i]='\0';
		// get the length
		len = strlen(str);
		// keep a record for the largest
		*max_len = (*max_len > len)? *max_len : len;
		*min_len = (*min_len < len)? *min_len : len;
		// store 
		push(s, len, offset_previous);
		offset_previous=ftell(fp);
	}
	
}

void show_all_possible_combinations(node_t *i, node_t *j, size_t max_len, size_t current_len)
{
	if((j!=NULL) && (j->len + current_len) <= max_len){
		current_len= j->len + current_len;
		printf("current_len=%d\tword_offset=%d\n", (int) current_len, (int) j->offset);
		show_all_possible_combinations(i, j->next, max_len, current_len);
	} //else if (j!=NULL)
		//show_all_possible_combinations(i, j->next, max_len, current_len);
	//else  
	//	j=i->next;
	return ;
		
	
	

}

void offset_list( stack_t *s, size_t max_len)
{
	#if 0
	// create a strcut
	struct offset {
		off_t offset;
		struct offset *next; 
	} *wordlist = NULL;
	#endif
	// we are using passing by value for
	node_t *i, *j;
	for(i=s->top; i!=NULL ; i=i->next){
		for(j=i; j!=NULL; j->next){
		show_all_possible_combinations(i, j, max_len, 0);
		}
	} 

}

int main()
{
	// open a file to read
	FILE *fp =fopen("0_large_example_list.txt","r"); 
	// creating a stack to hold the metadata
	stack_t *s = (stack_t *) malloc (sizeof(stack_t));
	s->top=NULL;
	size_t min_len=0, max_len=0;
	// create the stack from a file
	create_the_stack(fp, s, &max_len, &min_len);
	printf("largest word is %d\nsmallest word is %d\n", (int) max_len, (int) min_len);
	// let print the biggest words that we found
	char str[MAX_WORD_LENGTH];
	node_t *j=NULL;
	for(j=s->top; j!=NULL; j=j->next)
		if(j->len == max_len){
			// let get this word
			// set the offset to this word
			fseek(fp, j->offset, SEEK_SET );
			fgets(str,MAX_WORD_LENGTH,fp);
			// print the word
			printf("len=%d\tword=%s\n", (int) j->len, str);
		}
 	
 	//
 	offset_list(s, max_len);
 	// done -- cleanup
 	stack_t *done;
	for(done=s; done->top != NULL ; /*no need!! pop() does it*/)
		pop(done);
	free(s);
	fclose(fp);	
        return 0;

}
