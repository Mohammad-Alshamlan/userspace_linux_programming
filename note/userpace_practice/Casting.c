/*

source: http://how-to.linuxcareer.com/c-development-on-linux-types-variables-operators

In a nutshell, casting is forcing the compiler to forget about a variable's type and treat as having another type that you supply. This isn't done randomly, only between compatible types, and care is recommended when using casting. For example, let's say we want to find out the ASCII value of 'a'. The code could look like this:

*/


#include <stdio.h>

int main()
{
  char c = 'a';
  printf("The ASCII value of 'a' is %d.\n", (int)c);
  
  return 0;
}
