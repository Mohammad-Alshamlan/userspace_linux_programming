/*
 * Can you explain pointer to two dimensional arrays in c by an example?
 */

//Explanation:
//Examples of pointers to 2 dimensional arrays:

// Note: it does work, but I don't understand it at all!!!
#include<stdio.h>
void main()
{
	long array[][3]={7l,14l,21l,28l,35l,42l};
	long int (*ptr)[2][3]=&array;
	printf("%li ",-0[1[0[ptr]]]);
	return 0;
}
/*
Output: -28
Explanation:
-0[1[0[ptr]]]
=-1[0[ptr]][0] //From rule array[i]=i[array]
=-0[ptr][1][0]
=-ptr [0] [1] [0]
=-*ptr [0] [1] //From rule array[i]=*(array+i)
=-*(&array) [0] [1]
=-(&array) [0] [1][0]
=-(*&array)[1][0] //From rule *&p=p
=-array[1][0]
array[1][0] means 1*(3)+ 0 = 3rd element of array starting from zero i.e. 28
*/
