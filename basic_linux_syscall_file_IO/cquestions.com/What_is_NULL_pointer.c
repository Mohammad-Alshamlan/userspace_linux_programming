/*
 * What is NULL pointer?
 */
/*
Explanation:
Literal meaning of NULL pointer is a pointer which is pointing to nothing. NULL pointer points the base address of segment.

Examples of NULL pointer:

1. int *ptr=(char *)0;
2. float *ptr=(float *)0;
3. char *ptr=(char *)0;
4. double *ptr=(double *)0;
5. char *ptr=’\0’;
6. int *ptr=NULL;

What is meaning of NULL?
Answer:

NULL is macro constant which has been defined in the heard file stdio.h, alloc.h, mem.h, stddef.h and stdlib.h as
#define NULL 0

Examples:
(1)What will be output of following c program?
*/

#include "stdio.h"
int main()
{
	if(!NULL)
	printf("I know preprocessor");
	else
	printf("I don't know preprocessor");
}
/*
Output: I know preprocessor

Explanation:
!NULL = !0 = 1
In if condition any non-zero number mean true.

(2)What will be output of following c program?

#include "stdio.h"
int main()
{
	int i;
	static int count;
	for(i=NULL;i<=5;){
		count++;
		i+=2;
	}
	printf("%d",count);
}

Output: 3

(3)What will be output of following c program?

#include "stdio.h"
int main()
{
	#ifndef NULL
	#define NULL 5
	#endif
	printf("%d",NULL+sizeof(NULL));
}

Output: 2
Explanation:
NULL + sizeof(NULL)
=0 + sizeoof(0)
=0+2 //size of int data type is two byte.

We cannot copy anything in the NULL pointer.

Example:

(4)What will be output of following c program?

#include "string.h"
int main()
{
	char *str=NULL;
	strcpy(str,"c-pointer.blogspot.com");
	printf("%s",str);
	return 0;
}

Output: (null)
 
