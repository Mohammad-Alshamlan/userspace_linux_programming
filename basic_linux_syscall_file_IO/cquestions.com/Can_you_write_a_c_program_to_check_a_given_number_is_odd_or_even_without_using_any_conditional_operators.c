/*
 * Can you write a c program to check a given number is odd or even without using any conditional operators?
 */ 
 
#include <stdio.h>
int fun();

int main(int argc, char *argv[]){         
    int num;
    scanf("%d",&num);
    if(num&1)
         printf("odd");
    else
         printf("even");
    return 0;
}
