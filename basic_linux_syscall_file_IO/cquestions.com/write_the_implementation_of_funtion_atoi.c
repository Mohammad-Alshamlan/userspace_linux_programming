/*
 * This is a rough implementation of function atoi()
 */
 
#include<stdio.h>

int atoi_(char *str)
{
	int num = 0;
	// pointer algrothim instead of 'i' and for-loop
	while( *str != '\0' )
		num = num * 10 + *(str++) - '0' ;
	return num;
}

int main(int argc, char *argv[])
{
	// error check for command-line arguments
	if(argc < 2){
		fprintf(stderr, "please, do it as follows:\n\t(bash) $ %s <number>\n", argv[0]);
	}
	// convert	
	printf("%s=%d\n!!",argv[1], atoi_(argv[1]));
	return 0; 
}

/*
Example:
	alshamlan@alshamlan-K55A:/tmp/interview$ make q1 -B
	cc -g -Wall    q1.c   -o q1
	alshamlan@alshamlan-K55A:/tmp/interview$ ./q1 
	please, do it as follows:
		(bash) $ ./q1 <number>
	alshamlan@alshamlan-K55A:/tmp/interview$ ./q1 11
	11=11
	alshamlan@alshamlan-K55A:/tmp/interview$ 
*/
