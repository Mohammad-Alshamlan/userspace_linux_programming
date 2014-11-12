/*
 * What is a multilevel pointer in c?
 */ 
 
/*
Explanation:
A pointer is pointer to another pointer which can be pointer to others pointers and so on is known as multilevel pointers. We can have any level of pointers. Examples of multilevel pointers in c:
(1) What will be output if you will execute following code?
*/

#include<stdio.h>
int main()
{
	int s=2,*r=&s,**q=&r,***p=&q;
	printf("%d",p[0][0][0]);
	return 0;
}

/*
Output: 2
Explanation: 
As we know p[i] =*(p+i)
So,
P[0][0][0]=*(p[0][0]+0)=**p[0]=***p
Another rule is: *&i=i
So,
***p=*** (&q) =**q=** (&r) =*r=*(&s) =s=2
(2) What will be output if you will execute following code?

#include<stdio.h>
#define int int*
int main()
{
	int *p,q;
	p=(int *)5;
	q=10;
	printf("%d",q+p);
	return 0;
}
Output: 25
Explanation: If you will see intermediate file you will find following code:

#include<stdio.h>
void main()
{
	int **p,q;
	p=(int **)5;
	q=10;
	printf("%d",q+p);
	return 0;
}

Explanations:
Here q pointer and p is a number.
In c, Address + number = Address
So, New address = old address + number * Size of data type to which pointer is pointing.
= 5 + 10 * sizeof (*int)
= 5+10*2 = 25.
Note: We are assuming default pointer is near. Actually it depends upon memory model.
*/
