/*
 * program takes an input from argv[1] and then prints 
 * fibonacci sequence upto the given number?
 */
#include<stdio.h>
#include<stdlib.h>

int fabo (int num)
{
	int i, j, tmp;
	// we want j=0 because fibonacci sequence starts as 1 1 2 3
	// so to consider the repetition of two 1's we need to
	// count with another variable other than 'i', which in case 
	// is 'j'
	for(i=1, j=0; i <= num ; /* we will do this in the body */){
		printf("%d\t", i); 
		// because we are printing before getting to this condition
		// we simply use (j < 1) and not ( j <= i), again this due to place of the print
		// Now, if (j<1) == false, then use tmp as before running fibonacci sequence algorithm
		// which in ower case is "i += j"
		(j < 1) ? j++ : (tmp=i, i += j, j = tmp);	
	}
}


int main (int argc, char *argv[])
{
	printf("Upto %s\n", argv[1]);
	fabo(atoi(argv[1]));
	return !puts(" ");
}

/*
//output

alshamlan@alshamlan-OptiPlex-980:/tmp/interview$ ./q1 1000
Upto 1000
1	1	2	3	5	8	13	21	34	55	89	144	233	377	610	987	 
alshamlan@alshamlan-OptiPlex-980:/tmp/interview$ ./q1 987
Upto 987
1	1	2	3	5	8	13	21	34	55	89	144	233	377	610	987	 
alshamlan@alshamlan-OptiPlex-980:/tmp/interview$ ./q1 986
Upto 986
1	1	2	3	5	8	13	21	34	55	89	144	233	377	610	 
alshamlan@alshamlan-OptiPlex-980:/tmp/interview$ 

*/
