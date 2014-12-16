/*  <incomplete>!!!
 * the idea is to create a simplified linkedlist then I ever did!!
 * [1] we sill assume that the biggest word possible is 32 letters, and there is no way that we would have bigger than 32
 * [2] I need to sort the linkedlist from biggest to the smallest
 * [3] So, I have the file is alphptically sorted from 'a' to 'z', and the linkedlist is length sorted from the bigest to the smallest
 * [4] also, the alphiptical sorted comes from the file, so the offset has a relationship with this 
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

// idea: *head is the only element isn't sorted, so just sort *head to its place!!
void sort(node_t **head)
{
	node_t *unsorted=*head, *i=(*head)->next, *previous=NULL;
	while( (i!=NULL) && ((unsorted->len) < (i->len) )){
		previous=i;
		i=i->next;	
	}
	if(i!=(*head)->next){
		/* if we started with this example: [11]->[44]->[33]->[22]->[00]->NULL
		 * now, we have the following: unsorted==[11], unsorted->next=[44], i==[00], and previous==[22]
		 */
		 *head=unsorted->next;
		 unsorted->next=i;
		 previous->next=unsorted;
	 }
}


void create_the_linkedlist(FILE *fp, node_t *head)
{
	char str[MAX_WORD_LENGTH];
	size_t min_len=0, max_len=0, len;
	long offset_previous=0;
	int i;
	// the head of linkedlist

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
		// sort
		sort(&head);
		offset_previous=ftell(fp);
	}
	printf("largest word is %d\nsmallest word is %d\n", (int) max_len, (int) min_len);
	//
	// printing top ten lengthest words
	node_t *j;
	for(i=0, j=head; (i<10) && (j!=NULL); i++, j=j->next){
		// let get this word
		// set the offset to this word
		fseek(fp, j->offset, SEEK_SET );
		fgets(str,MAX_WORD_LENGTH,fp);
		// print the word
		printf("len=%d\tword=%s\n", (int) j->len, str);
	}

}

int main(int argc, char *argv[])
{
	if(argc < 2){
		perror("you are missing command-line argument\nPlease, include the file name\n");
		exit(EXIT_FAILURE);
	}
	// create the needed var's
	FILE *fp =fopen(argv[1],"r");
	node_t *head=NULL; 
	//
	create_the_linkedlist(fp, head);
	// delete all the nodes
	while(head!=NULL)
		node_deletion(&head);
 	fclose(fp);
        return 0;

}
