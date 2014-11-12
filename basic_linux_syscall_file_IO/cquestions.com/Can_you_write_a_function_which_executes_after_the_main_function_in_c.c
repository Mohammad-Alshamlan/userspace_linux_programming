/*
 * Can you write a function which executes after the main function in c?
 */
 
#include <stdio.h>
#include <stdlib.h>

void fun();
int main(int argc, char *argv[])
{
   atexit(fun);
   printf("cquestion");
   return 0;
}

void fun(){
  printf("bank");
}
