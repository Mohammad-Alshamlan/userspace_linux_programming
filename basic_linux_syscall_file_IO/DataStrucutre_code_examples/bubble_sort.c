/*
 *  bubble sort
 */
 #include<stdio.h>
 #include<stdlib.h>

void bubble (int *list, int n)
{
	int c,d,t;
	for(c=0; c<(n-1); c++) {
		for (d=0; d< (n - c-1) ; d++) {
			if( list[d] > list[d+1]){
				t=list[d];
				list[d]= list[d+1];
				list[d+1]=t;
			} 
		}
	}
}

int main(int argc, char *argv[])
 {
 	int list[]={2,4,6,8,0,9,7,5,3,1};
 	int i, len= (int) sizeof(list)/ sizeof(list[0]) ;
 	bubble(list, (len) );
 	for(i=0;i<len;i++)
 		printf("%d ", list[i]);
 	return !puts(" ");
 }
