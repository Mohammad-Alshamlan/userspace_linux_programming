/*
objective: I don't want the destanaction variable Arry to be larger or smaller than the source, I want it exatct!!
*/

#include<string.h> // if you're using string.h, then you don't need to import stdio.h!!

int main (){

char a[]= "hello world!!"; 
char b[strlen (a)];		// the same size as a[]

printf("%s\n\%s\n", a, b);
strcpy (b, a);  // note: b doesn't have anything that we stored into it, so the contant is garbage!!
printf ("%s\n%s\n", a, b);
return 0; // is better to have when main in int type
}
