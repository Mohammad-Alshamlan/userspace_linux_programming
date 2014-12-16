/*  <incomplete>!!!
 * the idea is to create a simplified linkedlist then I ever did!!
 * [1] we sill assume that the biggest word possible is 32 letters, and there is no way that we would have bigger than 32
 * [2] I need to sort the linkedlist from biggest to the smallest
 * [3] So, I have the file is alphptically sorted from 'a' to 'z', and the linkedlist is length sorted from the bigest to the smallest
 * [4] also, the alphiptical sorted comes from the file, so the offset has a direct relationship with alphptically order
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

void print_combination(node_t *holder[], size_t holder_index)
{
	int iterate;
	for(iterate=0; (iterate<holder_index) && (holder[iterate]!=NULL) ; iterate++)
		printf("%zu\t", holder[iterate]->len);
	printf("\n");
}

void show_combination (node_t *head, size_t limit)
{
	size_t iterate=0, current=0,  holder_index=0;
	node_t *holder[limit], *previous_holder[limit];
	node_t *i, *j;
	// search
	for(i=head; i!=NULL; i=i->next){
		// fix the first element for holder[0]
		holder_index=0;
		holder[holder_index]=i;
		holder_index++;
		// take the length of holder[0]->len (== i->len);
		current=i->len;
		// setup j
		j=head;
		while((j!=NULL)){
			// search
			if( ((current+j->len) < limit) && (holder_index<limit) ){
				current+=j->len;
				holder[holder_index]=j;
				holder_index++;
				j=head;
			} else if (((current+j->len) >= limit) && (holder_index<limit) && (holder_index>0)){
				j=j->next;
				/* 
				 * idea
				 * [1] make sure this is not the end of linkedlist
				 * [2] we don't want to reset holder[0] because the first loop will do it for us!! So, we will check 'current' value
				 * [3] make sure that the next node is not the end of linkedlist. It is pointless loop for it!! 
				 */
				if((j==NULL) && (current > holder[0]->len ) && (holder[holder_index -1]->next != NULL) ){
					// decrement  current
					current -= holder[holder_index -1]->len;
					// remove the previous node, replace it with less value
					holder[holder_index -1]=holder[holder_index -1]->next;
					// increment current with the new value
					current += holder[holder_index -1]->len;
					// reset 'j' to the value of the new 'current'
					j=holder[holder_index -1];
					
				}
			} 
			// Note, make sure you don't use repeated results
			// compare the old with the new
			for(iterate=0; iterate < limit ; iterate++)
				if(previous_holder[iterate]!=holder[iterate]){
					print_combination(holder, holder_index);
					// copy the current holder to the previous_holder even if it is grabage!!
					for(iterate=0; iterate < limit ; iterate++)
						previous_holder[iterate]=holder[iterate];
					break;
				}	

			
		}
		
	}

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
		// we don't want nodes that don't content a word
		if (len > 0) {
			// push it into the stack
			node_insertion(&head, len, offset_previous);
			// sort
			sort(&head);
		}
		offset_previous=ftell(fp);
	}
	// checkout all possible combinations
	show_combination(head, (head->len +1) );

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
