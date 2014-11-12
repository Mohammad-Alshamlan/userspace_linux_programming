/*
revering a string (this time revers complete words and not charchters!!)
*/
#include<string.h> // if you're using string.h, then you don't need to import stdio.h!!

int main (){

char * name[]={"Citrix","in","Florida"};	// create an array of pointers to a char, not a pointer to a char array!
printf("%s %s %s\n",name[0],name[1],name[2]) ;	// print the right order
int i;						// we are using ANSI style, so this is not part of for loop
for ( i=1 ; i<= strlen(name) ; i++)		// using i=1 and not i=0 because reversing issue with Null value!!
	printf("%s ", name[strlen(name) - i]);	// print the reverse values
printf("\n");					// just a new-line for the bash shell  
return 0; // is better to have when main in int type
}
