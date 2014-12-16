/*
 * I took the idea from MIT lecture
 */
#include<stdio.h>

void shift(int *list, int index)
{
	int j;
	for(j=list[index]; index && list[index -1] > j; index--)
		list[index]=list[index -1];
	list[index]=j;
}

void sort(int *list, size_t len)
{
	int i;
	for(i=1; i< (int) len; i++)
		if(list[i] < list[i -1])
			shift(list, i);
}

int main()
{
	int i, list[]={6,2,10,1,5,8,9,3,7,4};
	size_t len;
	sort(list, (len= sizeof(list)/sizeof(list[0])) );
	for(i=0; i<len; i++)
		printf("%d ", list[i]);
	return !puts(" ");	
}

/*
// combined function
	#include<stdio.h>

	void sort(int *list, int len)
	{
		int i, j, temp;
		for(i=1; i<len; i++)
			if(list[i -1] > list[i]){
				for(temp=list[i], j= i; j && temp<list[j -1]; j--)
					list[j]=list[j-1];
				list[j]=temp;
			}
	}

	int main()
	{
		int i, list[]={1,3,5,7,9,0,8,6,4,2};
		int len= (int) sizeof(list)/sizeof(list[0]);
		sort(list, len);
		for(i=0; i<len; i++)
			printf("%d", list[i]);
		return !puts(" ");
	}
*/
