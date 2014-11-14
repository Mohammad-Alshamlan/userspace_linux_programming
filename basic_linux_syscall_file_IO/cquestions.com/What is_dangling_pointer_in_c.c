/*
 * What is dangling pointer in c?
 */

/*
Explanation:
Dangling pointer:

If any pointer is pointing the memory address of any variable but after some variable has deleted from that memory location while pointer is still pointing such memory location. Such pointer is known as dangling pointer and this problem is known as dangling pointer problem.

For example:
What will be output of following c program?

	#include<stdio.h>

	int *call();
	int main(){
		int *ptr;
		ptr=call();
		fflush(stdin);
		printf("%d",*ptr);
		return 0;
	}
	int * call(){

		int x=25;
		++x;
		return &x;
	}

Output: Garbage value
Note: In some compiler you may get warning message returning address of local variable or temporary

Explanation: variable x is local variable. Its scope and lifetime is within the function call hence after returning address of x variable x became dead and pointer is still pointing ptr is still pointing to that location.
*/


//Solution of this problem: 
//Make the variable x is as static variable. In other words, we can say a pointer whose pointing object has been deleted is called dangling pointer.
#include<stdio.h>

int *call();
int main(){
	int *ptr;
	ptr=call();
	fflush(stdin);
	printf("%d",*ptr);
	return 0;
}
int * call(){
	static int x=25;
	++x;
	return &x;
}

//Output: 26

/* 
I found this work without function pointer:	
	#include<stdio.h>

	int call()
	{
		static int x=25;
		return &x;
	}

	int main()
	{
		int *px=call();
		return !printf("x=%d\n", *px);
	}

alshamlan@alshamlan-VGN-CR520E:/tmp/interview$ make -B q1
cc     q1.c   -o q1
q1.c: In function ‘call’:
q1.c:6:2: warning: return makes integer from pointer without a cast [enabled by default]
q1.c: In function ‘main’:
q1.c:11:10: warning: initialization makes pointer from integer without a cast [enabled by default]

also, I found that without using static variable it still works
	#include<stdio.h>

	int *call()
	{
		int x=25;
		return &x;
	}

	int main()
	{
		int *px=call();
		return !printf("x=%d\n", *px);
	}
alshamlan@alshamlan-VGN-CR520E:/tmp/interview$ make q1
cc     q1.c   -o q1
q1.c: In function ‘call’:
q1.c:6:2: warning: function returns address of local variable [enabled by default]
alshamlan@alshamlan-VGN-CR520E:/tmp/interview$ ./q1
x=25
alshamlan@alshamlan-VGN-CR520E:/tmp/interview$ 

*/


