/*
 * Write a c program to find size of structure without using sizeof operator?
 */
/*
The below code from the website, which gcc doesn't compile because there is an error
#include<stdio.h>

struct  ABC
{
    int a;
    float b;
    char c;
};
int main(){
    struct ABC *ptr=(struct ABC *)0;
    ptr++;
    printf("Size of structure is: %d",*ptr);
    return 0;
}
*/

// so I understood the concept, and I did mine!!
#include<stdio.h>

struct  ABC
{
    int a;
    float b;
    char c;
};
int main(){
    struct ABC *ptr=(struct ABC *)0;
    char *px = ptr; 
    char *py= ++ptr;
    int *pn1 = --ptr;
    int *pn2 = ++ptr;
    printf("Size of structure is: %zu\n", sizeof(struct ABC));
    printf("Size of structure is: %zu\n", 4* (pn2 - pn1)); // because int is 4 byets in this machine
    printf("Size of structure is: %zu\n", py - px); // because char is a byte!! so no multiplication is needed!!
    return 0;
}

/*
alshamlan@alshamlan-VGN-CR520E:/tmp/interview$ make q1
cc     q1.c   -o q1
q1.c: In function ‘main’:
q1.c:11:16: warning: initialization from incompatible pointer type [enabled by default]
q1.c:12:15: warning: initialization from incompatible pointer type [enabled by default]
q1.c:13:16: warning: initialization from incompatible pointer type [enabled by default]
q1.c:14:16: warning: initialization from incompatible pointer type [enabled by default]
alshamlan@alshamlan-VGN-CR520E:/tmp/interview$ make q1
make: `q1' is up to date.
alshamlan@alshamlan-VGN-CR520E:/tmp/interview$ ./q1
Size of structure is: 12
Size of structure is: 12
Size of structure is: 12
*/
