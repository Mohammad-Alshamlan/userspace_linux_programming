/*
 * Write a c program to reverse a string?
 */

// mine
#include<stdio.h>
#include<string.h>
#define MAX 30

int main()
{
	char str[]="Hello World!!";
	char temp[MAX];
	int i, len= (int) strlen(str);
	for(i=0; i<len ; i++) 
		temp[i]= str[len - i -1];
	temp[++i]='\0';
	strcpy(str, temp);
	return !printf("%s\n",str);	
}

/*
#include<stdio.h>
int main(){
    char str[50];
    char rev[50];
    int i=-1,j=0;

    printf("Enter any string : ");
    scanf("%s",str);
   
    while(str[++i]!='\0');

    while(i>=0)
     rev[j++] = str[--i];

    rev[j]='\0';
  
    printf("Reverse of string is : %s",rev);
  
    return 0;
}

Reverse a string in c using pointers
C program to reverse a string using pointers

#include<stdio.h>
int main(){
    char str[50];
    char rev[50];
    char *sptr = str;
    char *rptr = rev;
    int i=-1;

    printf("Enter any string : ");
    scanf("%s",str);
   
    while(*sptr){
     sptr++;
     i++;
    }

    while(i>=0){
     sptr--;
     *rptr = *sptr;
     rptr++;
     --i;
    }

    *rptr='\0';
  
    printf("Reverse of string is : %s",rev);
  
    return 0;
}


Sample output:
Enter any string : Pointer
Reverse of string is : retnioP
*/
