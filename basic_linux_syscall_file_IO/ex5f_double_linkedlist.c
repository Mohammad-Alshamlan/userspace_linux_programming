/*
 * creating a linkedlist that you can go backward if needed
 */ 

#include<stdio.h>
#include<stdlib.h>

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

void print_nodes_forward_and_backward(node_t *head)
{
	node_t *i, *j;
	// printing nodes forward 
	for(i=head; i!=NULL ; i=i->next){
		printf("forward:\t%zu\t<---\n", i->len);
		for(j=i; j!=NULL ; j=j->previous)
			printf("backward:\t%zu\n", j->len);
	}
}

int main(int argc, char *argv[])
{
	node_t *head=NULL;
	
	// adding nodes
	int i;
	for(i=0; i<LIMIT ; i++)
		node_insertion(&head, i);
	// print 
	print_nodes_forward_and_backward(head);		
	// delete all the nodes
	while(head!=NULL)
		node_deletion(&head);
	// done	
	return 0;	
}
