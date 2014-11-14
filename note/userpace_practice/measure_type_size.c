/*
source: http://how-to.linuxcareer.com/c-development-on-linux-types-variables-operators

description: this code tells you what the size in byte(s) for C types. 

Note:  If people will tell you that a byte is always eight bits, better think again. Every popular hardware architecture indeed uses eight-bit bytes, but there are exceptions, so don't make assumptions if you want to write portable code.

*/

#include <stdio.h>
#include <float.h>
#include <limits.h>

int main()
{
  unsigned long long ullmax = ULLONG_MAX;
  long lmax = LONG_MAX;
  long double ldmax = LDBL_MAX;
  
  printf("The max value of an unsigned long long is %Lu.\n", ullmax);
  printf("The max value of a long is %ld.\n", lmax);
  printf("The max value of a long double is %Lf.\n", ldmax);
  
  return 0;
}
