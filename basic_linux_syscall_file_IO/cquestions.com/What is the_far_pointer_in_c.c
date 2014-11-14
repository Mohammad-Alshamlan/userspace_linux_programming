/*
 * What is the far pointer in c?
 */
 
/*
Explanation:
The pointer which can point or access whole the residence memory of RAM i.e. which can access all 16 segments is known as far pointer.

Size of far pointer is 4 byte or 32 bit. Examples:
(1) What will be output of following c program?
*/
int main()
{
	int x=10;
	int far *ptr;
	ptr=&x;
	printf("%d",sizeof ptr);
	return 0;
}

/*
Output: 4

(2)What will be output of following c program?

int main()
{
int far *near*ptr;
printf("%d %d",sizeof(ptr) ,sizeof(*ptr));
return 0;
}

Output: 4 2
Explanation: ptr is far pointer while *ptr is near pointer.

(3)What will be output of following c program?

int main(){
int far *p,far *q;
printf("%d %d",sizeof(p) ,sizeof(q));
}

Output: 4 4

First 16 bit stores: Segment number
Next 16 bit stores: Offset address

Example:

int main(){
int x=100;
int far *ptr;
ptr=&x;
printf("%Fp",ptr);
return 0;
}

Output: 8FD8:FFF4
Here 8FD8 is segment address and FFF4 is offset address in hexadecimal number format.

Note: %Fp is used for print offset and segment address of pointer in printf function in hexadecimal number format.
In the header file dos.h there are three macro functions to get the offset address and segment address from far pointer and vice versa.

1. FP_OFF(): To get offset address from far address.
2. FP_SEG(): To get segment address from far address.
3. MK_FP(): To make far address from segment and offset address.

Examples:
(1)What will be output of following c program?

#include "dos.h"
int main(){
int i=25;
int far*ptr=&i;
printf("%X %X",FP_SEG(ptr),FP_OFF(ptr));
}

Output: Any segment and offset address in hexadecimal number format respectively.

(2)What will be output of following c program?

#include "dos.h"
int main(){
int i=25;
int far*ptr=&i;
unsigned int s,o;
s=FP_SEG(ptr);
o=FP_OFF(ptr);
printf("%Fp",MK_FP(s,o));
return 0;
}

Output: 8FD9:FFF4 (Assume)
Note: We cannot guess what will be offset address; segment address and far address of any far pointer .These address are decided by operating system.

Limitation of far pointer:

We cannot change or modify the segment address of given far address by applying any arithmetic operation on it. That is by using arithmetic operator we cannot jump from one segment to other segment. If you will increment the far address beyond the maximum value of its offset address instead of incrementing segment address it will repeat its offset address in cyclic order.

Example:

(q)What will be output of following c program?

int main(){
int i;
char far *ptr=(char *)0xB800FFFA;
for(i=0;i<=10;i++){
printf("%Fp \n",ptr);
ptr++;
}
return 0;
}

Output:

B800:FFFA
B800:FFFB
B800:FFFC
B800:FFFD
B800:FFFE
B800:FFFF
B800:0000
B800:0001
B800:0002
B800:0003
B800:0004

This property of far pointer is called cyclic nature of far pointer within same segment.

Important points about far pointer:

1. Far pointer compares both offset address and segment address with relational operators.

Examples:

(1)What will be output of following c program?

int main(){
int far *p=(int *)0X70230000;
int far *q=(int *)0XB0210000;
if(p==q)
printf("Both pointers are equal");
else
printf("Both pointers are not equal");
return 0;
}

Output: Both pointers are not equal

(2)What will be output of following c program?

int main(){
int far *p=(int *)0X70230000;
int far *q=(int *)0XB0210000;
int near *x,near*y;
x=(int near *)p;
y=(int near *)q;
if(x==y)
printf("Both pointer are equal");
else
printf("Both pointer are not equal");
return 0;
}

Output: Both pointers are equal

2. Far pointer doesn’t normalize.
