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
	struct node *next;
} node_t;

void node_insertion(node_t **head, size_t len)
{
	// creating and defining a new node
	node_t *new=(node_t *) malloc (sizeof(node_t));
	new->len=len;
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

int main()
{
	node_t *head=NULL;
	size_t array[]={22, 11, 44, 00, 33, 00, 55, 00, 22, 11, 22};
	// create nodes	
	size_t i, len;
	for(i=0, len=sizeof(array)/sizeof(array[0]); i < len; i++){
		node_insertion(&head, array[i]);
		sort(&head);
	}
	// show the linkedlist
	node_t *j;
	for(j=head; j!=NULL ; j=j->next)
		printf("%zu\n", j->len);
	// cleanup the heap
	while(head!=NULL)
		node_deletion(&head);
	return 0;

}
