/*
source:
http://cplus.about.com/library/downloads/tutorials/c/pointers2/ex1.c
*/

/* ex1 Single Linked List functions */
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dataElement {
  char * key;
  int id;
};

typedef struct dataElement * pElement;
typedef struct Node * pNode;
typedef char * pChar;


typedef struct Node {
  pNode next;
  pElement data;
};

int getNextID() {
	static int id=0;
	return id++;
}

/* how big is a Node? */
const nodeSize = sizeof(struct Node  );
const keySize = 16;
const elementSize = sizeof( struct dataElement );

// Create a new node, initialize it add it to the end of the list

pNode AddElement( pNode listtail )
{
	pNode result=0;

	result = malloc( nodeSize );
	if (result) {
		result->data = malloc( elementSize );
		if (result->data)
		{
			result->data->id=getNextID();
			result->data->key = (pChar)malloc(keySize+1);
			if (!result->data->key)
			{  /* failed so start destroying the element */
				free( result->data );
				result->data=0;
			}
		}

		if (!result->data)	/* element or its key failed so free up the node*/
		{
			free(result);
			result =0;
		}

	}
	/* If built ok add to end of list*/
	if (result) {
		if (!listtail)  /* we have an empty list! */
		{
			listtail = result;
		}
		else /* point the current tail to the new node */
		{
			listtail->next= result;
			listtail = result;  /* new node is now the tail */
		}
	}
	return result;
}


void printList( pNode head) {
	pElement element=0;
	while ( head )
	{
		element = head->data;
		printf("Id = %i Key = %s\n\r",element->id,element->key);
		head=head->next;
	}
}

pNode findKey(pNode head,pChar searchKey) {
    pElement element=0;
	int found =0;
	while (head) {
		element = head->data;
		if (strstr(element->key,searchKey ) )
		{
			return head;
		}
		else
		{
			head= head->next;
		}
	}
	return NULL;
}

void killList ( pNode head ) {
	pElement element=0;
	pNode    node =0;

	while ( head )
	{
		node = head;
		element = node->data;
		head = node->next;
		free( element->key );
		free( element );
		free( node ); 
	}
}

int main(int argc, char* argv[])
{
	int i;
	pNode head=0;
	pNode tail=0;
	pNode search=0;
	pElement element;
	pChar key= (pChar) malloc(keySize +1 );;

	for (i=0;i<100;++i) {
		tail = AddElement( tail );
		if (!tail)
			break; /* Something failed so add no more */

		if (i==1)
		{

			head=tail; /* heads points to the first node */
		}
		element=tail->data;
		sprintf( key, "KEYID:%i", i);
		strcpy(element->key, key);
	}

	if (head ) {
		search = findKey( head,"KEYID:78");
		if (search) {
			element=search->data;
			printf("found at element %i\n\r",element->id);
		}
		else
		{
			printf("Key not found");
		}
	}
	
	printList( head ); 
	killList( head );
	head=0;
	tail=0;
	free( key );
	return 0;
}

