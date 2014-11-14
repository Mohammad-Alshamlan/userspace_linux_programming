/*
 * Write a c program to modify the constant variable in c?
 */

/*
Explanation:
You can modify constant variable with the help of pointers. For example:
*/

#include<stdio.h>

int main()
{
	const int x=5;
	int *px= &x;
	*px=6;
	return !printf("x=%d\n", x);
}

/*
alshamlan@alshamlan-VGN-CR520E:/tmp/interview$ make q1
cc     q1.c   -o q1
q1.c: In function ‘main’:
q1.c:6:11: warning: initialization discards ‘const’ qualifier from pointer target type [enabled by default]
alshamlan@alshamlan-VGN-CR520E:/tmp/interview$ ./q1
x=6
alshamlan@alshamlan-VGN-CR520E:/tmp/interview$ 
*/
