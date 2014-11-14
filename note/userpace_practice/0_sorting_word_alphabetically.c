//

this program sorts words alphabetically.

	#include <stdio.h>
	#include <string.h>

	void alphabetical (char *a[])
	{
		int i=0, j;
		for (i = 0; a[i] ; i++) {
			for ( j = i+1; a[j] ; j++)
				if (strcmp(a[i], a[j]) > 0) {
					char* temp = a[i]; 
					a[i] = a[j]; 
					a[j] = temp; 
				}
		}
	}

	int main(void) {
		char *a[] = {"Florida", "Oregon", "Califoria", "Georgia", NULL};
		alphabetical(a);
		int i;
		for(i=0; a[i]; i++)
			printf("%s\n", a[i]);
		return 0;  
	}
/*
// output:
	alshamlan@alshamlan-VGN-CR520E:/tmp/interview$ make -B q1
	cc -g -Wall    q1.c   -o q1
	alshamlan@alshamlan-VGN-CR520E:/tmp/interview$ ./q1
	Califoria
	Florida
	Georgia
	Oregon
	alshamlan@alshamlan-VGN-CR520E:/tmp/interview$ 
*/

//--------------------------------
from Imagination Technologies interview follow up questions


	/*
	 * 1) Write a program 'sort' in c to sort a list of strings into alphabetical order. Do this without using any library string
	 * processing functions. Sample usage and expected output:
	 *	> sort defg abc aab xxxx
	 *	aab
	 *	abc
	 *	defg
	 *	xxxx
	 */
	 
	#include <stdio.h>

	// because I asked for not to use string.h, so I need to construct strcmp() function!!
	int strcmp_ (char *str1, char *str2)
	{
		while (*str1==*str2) {
			if(*str1=='\0')
				return(0);
			str1++;
			str2++;
		}
		return(*str1-*str2);
	}

	void alphabetical (char *a[])
	{
		// Note[1]: argv[0] is the prgram name, so we will skip it by making the iterator statrs at 1
		// Note[2]: argv[argc] is NULL, so we will use it to exit the for-statement loop 
		int i=1, j;
		for (i = 1; a[i] ; i++) {
			for ( j = i+1; a[j] ; j++)
				if (strcmp_(a[i], a[j]) > 0) {
					char* temp = a[i]; 
					a[i] = a[j]; 
					a[j] = temp; 
				}
		}
	}

	int main(int argc, char *argv[]) 
	{
		// check if the user inputs arguments. If not, then kill the program!!
		if (argc < 2)
			return printf("Please, you need to have arguments\n");
		alphabetical(argv);
		int i;
		// argv[argc] hasn't been changed, so when argv[argc]==NULL, the loop stops!!!
		// also, the iterator statrs at 1 because argv[0] hasn't been changed, so we skipped it
		for(i=1; argv[i]; i++)
			printf("%s\n", argv[i]);
		return 0;  
	}

/*
alshamlan@alshamlan-VGN-CR520E:~/Desktop/Imagination Technologies/quiz_coding$ make -B sort
cc -g -Wall    sort.c   -o sort
alshamlan@alshamlan-VGN-CR520E:~/Desktop/Imagination Technologies/quiz_coding$ ./sort 
Please, you need to have arguments
alshamlan@alshamlan-VGN-CR520E:~/Desktop/Imagination Technologies/quiz_coding$ ./sort aba bbb bab aab aaa abb 
aaa
aab
aba
abb
bab
bbb
alshamlan@alshamlan-VGN-CR520E:~/Desktop/Imagination Technologies/quiz_coding$ ./sort yyy ggg kkk qqq sss ccc
ccc
ggg
kkk
qqq
sss
yyy
alshamlan@alshamlan-VGN-CR520E:~/Desktop/Imagination Technologies/quiz_coding$ 
*/
