/*  <incomplete>!!!
 * the idea is to create a simplified linkedlist then I ever did!!
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

// creating linkedlist node
typedef struct node {
	size_t len;
	off_t offset;
	struct node *next;
} node_t;

void node_insertion(node_t **head, size_t len, off_t offset)
{
	// creating and defining a new node
	node_t *new=(node_t *) malloc (sizeof(node_t));
	new->len=len;
	new->offset=offset;
	// mapping the new node into the stack -- FIFO 
	new->next=*head;
	*head=new;
}

void node_deletion(node_t **head)
{
	node_t *remove=*head;
	// move forward
	*head=(*head)->next;
	// free the resource
	free(remove);
}

int main()
{
	FILE *fp =fopen("0_large_example_list.txt","r"); 
	char str[MAX_WORD_LENGTH];
	size_t min_len=0, max_len=0, len;
	long offset_previous=0;
	int i;
	// the head of linkedlist
	node_t *head=NULL;
	while((fgets(str,MAX_WORD_LENGTH,fp)) != NULL){
		// cleanup the word form '\n' and '\r'
		for (i=0; str[i] != '\0' ; i++)
			if((str[i]=='\n') || (str[i]=='\r'))
				str[i]='\0';
		// get the length
		len = strlen(str);
		// keep a record for the largest
		max_len = (max_len > len)? max_len : len;
		min_len = (min_len < len)? min_len : len;
		// push it into the stack
		node_insertion(&head, len, offset_previous);
		offset_previous=ftell(fp);
	}
	printf("largest word is %d\nsmallest word is %d\n", (int) max_len, (int) min_len);
	// let print the biggest words that we found
	node_t *j=NULL;
	for(j=head; j!=NULL; j=j->next)
		if(j->len == max_len){
			// let get this word
			// set the offset to this word
			fseek(fp, j->offset, SEEK_SET );
			fgets(str,MAX_WORD_LENGTH,fp);
			// print the word
			printf("len=%d\tword=%s\n", (int) j->len, str);
		}
	// delete all the nodes
	while(head!=NULL)
		node_deletion(&head);
 	fclose(fp);
        return 0;

}
