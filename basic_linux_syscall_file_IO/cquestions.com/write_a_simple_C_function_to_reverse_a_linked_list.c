/*
 * Write a simple C function to reverse a linked list?
 */
#include<stdio.h>
#include<stdlib.h>
#define LIMIT 5

/* Link list node */
typedef struct node {
	int data;
	struct node *next;
} node_t;

// add a new node onto the linkedlist
void add_node(node_t **head, int data)
{
	// create a new node
	node_t *new=(node_t *) malloc(sizeof(node_t *));
	if (new == NULL){
		perror("malloc() didn't work!!");
		exit(1);
	}
	// store the data onto the node storage
	new->data=data;
	// link the new node
	new->next=*head;
	*head=new;
}

/* Function to reverse the linked list */
void reverse_linkedlist(node_t **head)
{
	node_t *prev   = NULL;
	node_t *current = *head;
	node_t *next;
	while (current != NULL)	{
		next  = current->next;  
		current->next = prev;   
		prev = current;
		current = next;
	}
	*head = prev;
}

void printout_linkedlist(node_t *head)
{
	node_t *j;
	for(j=head; j!=NULL; j=j->next)
		printf("%d\t", j->data);
	// newline is needed!!
	puts(" ");
}

void remove_node(node_t **head)
{
	// setup a node points to the node that needs to be removed!!
	node_t *remove=*head;
	// move the head away from the node that needs to be removed!!
	*head=(*head)->next;
	// simply free the resource from the removed node
	free(remove);
	
}

int main(int argc, char *argv[])
{
	node_t *head=NULL;
	// populate the linkedlist 
	int i;
	for(i=0; i<LIMIT ; i++)
		add_node(&head, i);
	// print the linkedlist
	printout_linkedlist(head);
	// reverse the linkedlist
	reverse_linkedlist(&head);
	// print out the reversed linkedlist
	printout_linkedlist(head);
	// remove the allocated heap memory
	while(head != NULL)
		remove_node(&head);
	// done!!
	return 0;
}
