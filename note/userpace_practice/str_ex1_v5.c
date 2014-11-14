/*
from:	 /home/alshamlan/Desktop/Kernel engineer/Skills' Brush Up/1_C userspace/practice/str_ex1_v4.c

tutorial page: http://cplus.about.com/od/learningc/ss/strings_2.htm 
*/



/* ex4.c : */

#include "stdlib.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef char * string;

typedef struct wordrec * wordrecptr;
struct wordrec {
	string word;
	int count;
	wordrecptr next;
};

int ReadFile(string Filename,string buffer) {
	char c;
	FILE * fp;
	int filesize=0;
 if((fp=fopen(Filename,"r"))==NULL){
   perror("fopen");
   return -1;
 }
 while((c=getc(fp))!=EOF){
	 *buffer++=c;
	 filesize++;
 }
 *buffer='\0';
 return filesize;
 fclose(fp);
}

/* This adds a word to a list- if it's already there, it finds it and increments the count
   or it adds it on the end of the list */
void addword( string word,wordrecptr * list) {
	wordrecptr head = *list;
	wordrecptr prev = 0;
	while (head) {
		if (strcmp(head->word,word)) {
			prev=head;
			head=head->next;
		}
		else
		{
			head->count++;
			return;
		}
	}
	/* If here- didn't find word in list so create new struct 
     First time prev and head are both 0 so create new prev 
	 and set all fields to 0 with memset */
	if (!prev) 
	{
		prev= malloc(sizeof(struct wordrec));
		head=prev;
		*list = head;
	}
	else
	{
		prev->next =malloc(sizeof(struct wordrec));
		head= prev->next;
		
	}
	head->next =0; /* new end of list */
	head->count=1;
	head->word=malloc( strlen(word) +1 ); /* DFTTZ! */
	strcpy(head->word,word); 
	
}

int process( string input,wordrecptr * list) {
	int count=0;
	int len = strlen( input );
	int i;
	int inword=0; /* flag */
	string aword=malloc(32); /* should be long enough for the longest word! */
	string pword=aword;
	char c;
	string temp=input;
	for (i=0;i< len; i++) {
		c = *(temp++);
		if (isalpha(c)) {
			if (!inword ) {  /* start new word */	 
				pword=aword;
				inword=1;
			}				
			*pword++=c;
		}
		else
		{ // Add word to list
			if (pword != aword) 
				*pword='\0';	/* terminate word */
			inword=0; /* no longer in word */
			addword(aword,list);
			*aword='\0';
			count++;
		}
	}
	/* add the last word */
	if (strlen(aword))
	{
		*pword='\0';
		addword(aword,list);
	}
	
	free(aword);
	return count;
}

int DumpList( wordrecptr list ) {
	wordrecptr head = list;
	wordrecptr prev;
	int		   strcount=0;	

	while (head) {
		prev= head;
		if (prev->count >10)
			printf("%d x %s\n\r",prev->count,prev->word);
		head= head->next; /* get next in list */
		free(prev->word);
		free(prev);
		strcount++;
	}
	return strcount;
}

int main(int argc, char* argv[])
{
	string buffer=malloc(200000);
	wordrecptr wordlist = 0;
	int wordcount;
	int strcount;

	int fs=ReadFile("test.txt",buffer);
	if ( fs >-1) {
		wordcount = process(buffer, &wordlist );

		printf("Dump of Words\n\r");
		strcount=DumpList(wordlist); /* also frees up list */		
		printf("File size =%d bytes\n\r",fs);
		printf("Number of words found = %d\n\r",wordcount);
		printf("Number of unique words = %d\n\r",strcount);
	}
	free(buffer);
	return 0;
}

