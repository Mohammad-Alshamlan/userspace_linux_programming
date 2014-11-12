/*
 * What is difference between uninitialized pointer and null pointer?
 */

/*
Explanation:
An uninitialized pointer is a pointer which points unknown memory location while null pointer is pointer which points a null value or base address of segment. For example: 
int *p;   //Uninitialized pointer
int *q= (int *)0;  //Null pointer
#include<stdio.h>
int *r=NULL;   //Null pointer

What will be output of following c program?
*/
#include<string.h>
#include<stdio.h>
int main()
{
    char *p;  		//Uninitialized pointer
    char *q=NULL;   	//Null pointer;
    strcpy(p,"cquestionbank");
    strcpy(q,"cquestionbank");
    
    printf("%s  %s",p,q);
    return 0;
}

//Output: cquestionbank (null)
