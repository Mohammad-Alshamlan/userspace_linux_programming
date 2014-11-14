/*
revering a string
*/
#include<string.h> // if you're using string.h, then you don't need to import stdio.h!!

int main (){

char a[]= "hello world!!";
for ( int i=0 ; i <= strlen(a) ; i++)	// for loop using strlen for string length
printf("%c", a[strlen (a) - i]);	// using backward approach in the for loop
printf("\n");				// just having a new-space for the bash schell command-line
return 0; // is better to have when main in int type
}
