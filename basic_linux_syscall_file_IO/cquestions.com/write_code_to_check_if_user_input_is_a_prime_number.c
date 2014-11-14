/*
 * check if a number is a prime of not
 */

 #include<stdio.h>
 #include<string.h>
 char *prime( int num) 
 {
 	int nc=0, i=0;
 	for (i=1; i<=num; i++)
 		(num%i == 0) ? nc++ : num;
 	return (nc == 2) ? "is" : "isn't";
 }
 
 int main (int argc, char *argv[])
 {
 	printf("%d %s a prime number\n", atoi(argv[1]), prime(atoi(argv[1])));
 	return 0;
 }
 
  /*
 prime number must just have two multiple which are: itself, and with number 1. Therefore, more than two contraduct the prime rule, and lead to not a prime number. 
 
 Algrothim:
 if A is a prime number, but it doesn't equal itself nor 1. The reminder must be a nonzero. 
  
  */

