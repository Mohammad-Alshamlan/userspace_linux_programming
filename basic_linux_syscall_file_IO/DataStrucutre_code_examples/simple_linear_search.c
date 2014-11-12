/*
 * I took the idea from MIT
 */

#include<stdio.h>
#include<stdlib.h>

int *linear_search(int val, int *list, size_t len)
{
	int *pi = list, *pmax= list + (int)len;
	for (pi= list; pi < pmax; pi++)
		if (*pi == val)
			return pi;
	return NULL;
}

int main(int argc, char *argv[])
{
	int list[]={1,2,3,4,5,6,7,8,9, 10,11};
	int *p = linear_search(atoi(argv[1]), list, sizeof(list)/sizeof(list[0]));
	if(p)
		return !printf("%s is found in address %p\n", argv[1], p);
	return puts("Not found!!");
}
