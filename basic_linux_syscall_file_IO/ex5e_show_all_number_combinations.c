/*
 * creating a linkedlist that you can go backward if needed
 */ 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LIMIT 5

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

void show (node_t *head)
{
	size_t limit=LIMIT, current=0, *holder[LIMIT], holder_index=0;
	int depth=0, shift;
	node_t *i=head;
	while(i!=NULL){
		// 
		int print;
		for(print=0; print<holder_index; print++)
			printf("%zu\t", *holder[print]);
		printf("\n");
		// search
		if( ((current+i->len) < limit) && (holder_index<limit) ){
			current+=i->len;
			holder[holder_index]=&(i->len);
			holder_index++;
			i=head;
		} else if (((current+i->len) >= limit) && (holder_index<limit) && (holder_index>0)){
			i=i->next;
			//holder_index--;
		} else { // when  (holder_index>=limit)
			shift=++depth;
			//holder_index--;
			holder_index=0;
			//shift=--holder_index;
			while(shift--){
				current-=i->len;
				i=i->next;
				//current-=i->len;
			}	
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
