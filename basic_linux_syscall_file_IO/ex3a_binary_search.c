#include<stdio.h>
#include<stdlib.h>

void shift(int index, int *list, size_t len)
{
	int temp;
	/* the smallest value is in the far left, so list[index - i] <= list[index]  */
	for(temp= list[index]; index && list[index -1]> temp; index--)
		list[index]= list[index -1];
	list[index]= temp;
}

void insertion_sort (int *list, size_t len)
{
	int i;
	for(i=1; i<(int)len; i++)
		if(list[i] < list[i -1])
			shift(i, list, len);
}

int *binary_search(int val, int *list, size_t len)
{
	int L=0, R=(int)len, M;
	if(val <= list[len -1]){
	while(L<R){
		M=(L+R-1)/2;
		if(val==list[M])
			return &list[M];
		else if(val < list[M])
			R=M;
		else if (val > list[M]) 
			L=M+1; // adding one here is important because if doesn't it will be infint loop!! 
		}
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	if(argc < 2){
		perror("you are missing command-line argument\nPlease, include the file name\n");
		exit(EXIT_FAILURE);
	}
	// 
	int list[]={2,5,4,7,6,1,3,9,8,10,11,12,13};
	size_t len;
	insertion_sort(list, (len = sizeof(list)/sizeof(list[0])) );
	// binary search needs sorted list
	int *p= binary_search(atoi(argv[1]), list, len);
	if(p)
		return !printf("%s found in this address %p\n", argv[1], p);
	return !puts("Sorry, isn't found!!");
	
}
