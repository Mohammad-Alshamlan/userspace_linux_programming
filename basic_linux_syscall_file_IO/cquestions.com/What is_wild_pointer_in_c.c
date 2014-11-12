/*
 * What is wild pointer in c?
 */

/*
Explanation:
A pointer in c which has not been initialized is known as wild pointer.
*/

//Example:
//What will be output of following c program?
int main(){
	int *ptr;
	printf("%u\n",ptr);
	printf("%d",*ptr);
	return 0;
}

/*
Output: Any address
Garbage value

Here ptr is wild pointer because it has not been initialized. There is difference between the NULL pointer and wild pointer. Null pointer points the base address of segment while wild pointer doesn’t point any specific memory location.
*/
