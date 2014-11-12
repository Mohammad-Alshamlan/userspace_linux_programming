/*
 * Swap two variables without using third variable.
 */
 
#include<stdio.h>
#include<stdlib.h>

void swap(int *a, int *b)
{
	/* Idea
	a=A and b=B ==> a=A+B and b=B ==> a=A+B and b=-B ==> a=A+B and b=A ==> a=B and b=A 
	*/
	*a+=*b;
	*b*=-1;
	*b+=*a;
	*a-=*b;
}

int main(int argc, char *argv[])
{
	int a=atoi(argv[1]), b=atoi(argv[2]);
	printf("Before argv[1]=%d and argv[2]=%d\n", a, b);
	swap(&a,&b);
	return !printf("after argv[1]=%d and argv[2]=%d\n", a, b);
}

/*
#include<stdio.h>
int main(){
    int a=5,b=10;
//process one
    a=b+a;
    b=a-b;
    a=a-b;
    printf("a= %d  b=  %d",a,b);

//process two
    a=5;
    b=10;
    a=a+b-(b=a);
    printf("\na= %d  b=  %d",a,b);
//process three
    a=5;
    b=10;
    a=a^b;
    b=a^b;
    a=b^a;
    printf("\na= %d  b=  %d",a,b);
   
//process four
    a=5;
    b=10;
    a=b-~a-1;
    b=a+~b+1;
    a=a+~b+1;
    printf("\na= %d  b=  %d",a,b);
   
//process five
    a=5,
    b=10;
    a=b+a,b=a-b,a=a-b;
    printf("\na= %d  b=  %d",a,b);
    return 0;
}
*/
