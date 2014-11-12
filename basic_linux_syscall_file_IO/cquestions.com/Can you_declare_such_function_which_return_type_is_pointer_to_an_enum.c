/*
 *  Can you declare such function which return type is pointer to an enum?
 */
 
//Explanation: it works!!!!
#include <stdio.h>

typedef enum color{a,b,c,d,e}co;
enum color eee(){
    static co x;
    x=b+c/2;
    return x;
}

int main(){
    int num;
    num=eee();
    printf("%#d",num);
    return 0;
}

//Output: 2
