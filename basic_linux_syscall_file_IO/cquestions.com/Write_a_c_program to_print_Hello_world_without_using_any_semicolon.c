/*
 * Write a c program to print Hello world without using any semicolon
 */
 
#include<stdio.h>

void main()
{
	if(printf("Hello World!!\n")) {}
}

/*
Solution: 1
void main(){
    if(printf("Hello world")){
    }
}

Solution: 2
void main(){
    while(!printf("Hello world")){
    }
}

Solution: 3
void main(){
    switch(printf("Hello world")){
    }
}
*/
