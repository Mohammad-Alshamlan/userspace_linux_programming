/*
from:	 http://cplus.about.com/library/downloads/tutorials/c/strings/ex1.c

tutorial page: http://cplus.about.com/od/learningc/ss/strings_2.htm 
*/

/* ex1.c : */

#include "stdlib.h"	// I'm not quetty sure why this is used here!!
#include <stdio.h>


typedef char * string;

string a="A Long string";

string Left(string Source,int NewLen) {

	string result;
	string temp;
	if (NewLen <=0) 
		NewLen =1; /* Minimum length */

	result = (string)malloc(NewLen + 1); /* +1 = DFTTZ! */
	*result=' ';   /* default for unassigned strings */
	temp=result;
	if (Source && *Source)  /* don't copy an empty string */
	{
		while (NewLen-- >0)
			*temp++=*Source++;
	}
	else temp++;
	*temp='\0';
	return result;
}

string Mid( string Source,int Start,int Length) {
	string result;
	string temp;
	if (Start <0) 
		Start=1;
	if (Length <=0) 
		Length =1; /* Minimum length */
	result = (string)malloc(Length + 1); /* +1 = DFTTZ! */
	temp = result;
	if (Source)
	{
		while (*Source++ && --Start);
		if (*Source)  /* don't copy an empty string */
		{
			while (Length-- >0)
				*temp++=*Source++;
		}
	}
	*temp='\0';
	return result;
}

string Right(string Source,int NewLen) {
	string result;
	string temp;
	int	   Length=0;	
	if (NewLen <=0) 
		NewLen =1; /* Minimum length */
	result = (string)malloc(NewLen + 1); /* +1 = DFTTZ! */
	temp = result;

	if (Source)
	{
		while (*Source++)
			Length++;
		while (NewLen-- >=0 && Length-- >=0) 
			Source--;
		if (*Source)  /* don't copy an empty string */
		{
			while (*Source)
				*temp++=*Source++;
			
		}
	}
	*temp='\0';
	return result;
}


int main(int argc, char* argv[])
{
    string b= Left(a,5);
	string c= Left(0,-9);
	string d= Left("",1);
	string e= Mid(a,2,3);
	string f =Right(a,5); 
	string g =Right("Short",10);

	printf("a=%s<eol>\n\rb=%s<eol>\n\rc=%s<eol>\n\rd=%s<eol>\n\r",a,b,c,d);
	printf("e=%s<eol>\n\rf=%s<eol>\n\rg=%s<eol>\n\r",e,f,g);

	free(g);
	free(f);
	free(e);
	free(d);
	free(c);
	free(b);
	
	return 0;
}

