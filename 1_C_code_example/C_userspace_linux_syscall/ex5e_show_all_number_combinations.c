/*
 * creating a linkedlist that you can go backward if needed
 */ 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LIMIT 7
typedef struct node {
	size_t len;
	struct node *next;
	struct node *previous;
} node_t;

void node_insertion(node_t **head, size_t len)
{	
	// creating a new node
	node_t *new= (node_t *) malloc (sizeof(node_t));
	new->len=len;
	// mapping the new node
	if(*head==NULL)
		new->next=*head;
	else 
		(*head)->previous=new;
	new->next=*head;
	*head=new;
}

void node_deletion(node_t **head)
{
	node_t *remove=*head;
	// move forward
	*head=(*head)->next;
	// simply make (*head)->previous stops here (in this updated head)!!
	if(*head!=NULL)
		(*head)->previous=NULL;
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

void show (node_t *head)
{
	size_t limit=LIMIT, iterate, current=0,  holder_index=0;
	node_t *holder[LIMIT], *previous_holder[LIMIT];
	node_t *i=head;
	while(i!=NULL){	
		// copy the current holder to the previous_holder even if it is grabage!!
		for(iterate=0; iterate < limit ; iterate++)
			previous_holder[iterate]=holder[iterate];		
		// search
		if( ((current+i->len) < limit) && (holder_index<limit) ){
			current+=i->len;
			holder[holder_index]=i;
			holder_index++;
			i=head;
		} else if (((current+i->len) >= limit) && (holder_index<limit) && (holder_index>0)){
			i=i->next;
		} else { // when  (holder_index>=limit)
			// first decrease holder_index
			holder_index--;			
			while( (holder_index > 0) && (holder[holder_index] != NULL) && (holder[holder_index]->next == NULL))
				// decrease holder_index more!!
				holder_index--;	
			// break when the first element is null!!
			if(holder[0]==NULL)
				return;
			holder[holder_index]=holder[holder_index]->next;
			holder_index++;
			// measure current again
			current=0;
			for(iterate=0; (iterate<holder_index) && (holder[iterate]!=NULL) ; iterate++)
				current+=holder[iterate]->len;
		}
		// Note, make sure you don't use repeated results
		// compare the old with the new
		for(iterate=0; iterate < limit ; iterate++)
			if(previous_holder[iterate]!=holder[iterate]){
				print_combination(holder, holder_index);
				break;
			}	

	}
}

int main(int argc, char *argv[])
{
	node_t *head=NULL;
	
	// adding nodes
	int i;
	for(i=0; i<LIMIT ; i++)
		node_insertion(&head, i);
	// show all combination
	show(head);
	// delete all the nodes
	while(head!=NULL)
		node_deletion(&head);
	// done	
	return 0;	
}
