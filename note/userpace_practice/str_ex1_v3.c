/*
from:	 http://cplus.about.com/library/downloads/tutorials/c/strings/ex3.c

tutorial page: http://cplus.about.com/od/learningc/ss/strings_2.htm 
*/

/* ex3.c : */

#include "stdlib.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef char * string;

struct s {
	char  name[20];
	int age;
	char pin[9];  /* DFTTZ! */
};

typedef struct s badge;

int main(int argc, char* argv[])
{

	int i;
	printf(" ## C   Al Ap Ic Id Ig Ip Iu Is Ix\n\r");
	for (i=0;i<128;i++) {
		printf("%2d ",i);
		if (isalpha(i))
			printf("%c  ",i);
		else
			printf("   ");

		printf("%3d %2d %2d %2d %2d %2d %2d %2d %2d\n\r",
			isalnum(i),
			isalpha(i),
			iscntrl(i),
			isdigit(i),	 
			isgraph(i),	
			isprint(i),
			ispunct(i),
			isspace(i),
			isxdigit(i)	
		
		);
		if ((i+1) %8==0) /* space every 8 lines */
			printf("\n\r");
	}
	return 0;
}

