/*
from:	 http://cplus.about.com/od/learningc/ss/strings_6.htm

tutorial page: http://cplus.about.com/od/learningc/ss/strings_2.htm 
*/

/* ex4.c : */

#include "stdlib.h"
#include <stdio.h>
#include <string.h>

typedef char * string;

int main(int argc, char* argv[])
{

  string a="A very Long String";
  string b=" and now even longer!";
  string c=malloc(strlen(a) + strlen(b)+1) ; /* +1 DFTTZ! */
  strcpy(c,a) ;
  strcat(c,b) ;
  printf("c = %s\n",c) ;
  free(c) ;
  return 0;
}
