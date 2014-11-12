/*
from:	 http://cplus.about.com/library/downloads/tutorials/c/strings/ex2.c

tutorial page: http://cplus.about.com/od/learningc/ss/strings_2.htm 
*/


/* ex2.c : */

#include "stdlib.h" // I don't know why this one is used!!
#include <stdio.h>	// there is no need to include this if you import string.h in your code
#include <string.h>

typedef char * string;

struct s {
	char  name[20];
	int age;
	char pin[9];  /* DFTTZ! */
};

typedef struct s badge;

int main(int argc, char* argv[])
{
	badge b1,b2;
	memset(&b1,0,sizeof(b1));
	memset(&b2,0,sizeof(b1));
	b1.age=78;
	strcpy(b1.name,"My Name");
	strcpy(b1.pin,"01234567"); // DFTTZ!
	memcpy(&b2,&b1,sizeof(b1));
	printf("Name = %s Age = %d Pin = %s\n",b2.name,b2.age,b2.pin);
	return 0;
}

