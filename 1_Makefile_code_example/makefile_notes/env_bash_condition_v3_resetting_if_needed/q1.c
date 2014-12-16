#include<stdio.h>
#include<stdlib.h>

int atoi_ (char *str)
{
	int i, num;
	for (i=0, num=0; str[i]!='\0'; i++)
		num = num * 10 + str[i] - '0';
	return num;
}

int main (int argc, char *argv[])
{
	return !printf("%s=%d\n", argv[1], atoi_(argv[1]));
}


