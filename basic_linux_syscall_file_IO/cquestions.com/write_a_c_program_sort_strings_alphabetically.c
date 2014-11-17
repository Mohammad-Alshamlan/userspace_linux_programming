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
