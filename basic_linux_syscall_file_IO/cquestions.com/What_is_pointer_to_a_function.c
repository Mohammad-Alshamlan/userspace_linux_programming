/*
 * What is pointer to a function?
 */

/*
Explanation:
(1) What will be output if you will execute following code?
*/
#include<stdio.h>

int * function();
int main()
{
	auto int *x;
	int *(*ptr)();
	ptr=&function;
	x=(*ptr)();
	printf("%d\n",*x);
}
int *function()
{
	static int a=10;
	return &a;
}

//Output: 10

/*
Explanation: Here function is function whose parameter is void data type and return type is pointer to int data type.

x=(*ptr)()
=> x=(*&functyion)() //ptr=&function
=> x=function() //From rule *&p=p
=> x=&a
So, *x = *&a = a =10

(2) What will be output if you will execute following code?

int find(char);
int(*function())(char);
int main()
{
	int x;
	int(*ptr)(char);
	ptr=function();
	x=(*ptr)('A');
	printf("%d\n",x);
	return 0;
}
int find(char c)
{
	return c;
}
int(*function())(char)
{
	return find;
}

Output: 65
Explanation: Here function whose name is function which passing void data type and returning another function whose parameter is char data type and return type is int data type.

x=(*ptr)(‘A’)
=> x= (*function ()) (‘A’) //ptr=function ()
//&find=function () i.e. return type of function ()
=> x= (* &find) (‘A’)
=> x= find (‘A’) //From rule*&p=p
=> x= 65

(3) What will be output if you will execute following code?
char * call(int *,float *);
int main()
{
	char *string;
	int a=2;
	float b=2.0l;
	char *(*ptr)(int*,float *);
	ptr=&call;
	string=(*ptr)(&a,&b);
	printf("%s",string);
	return 0;
}
char *call(int *i,float *j)
{
	static char *str="c-pointer.blogspot.com";
	str=str+*i+(int)(*j);
	return str;
}

Output: inter.blogspot.com
Explanation: Here call is function whose return type is pointer to character and one parameter is pointer to int data type and second parameter is pointer to float data type and ptr is pointer to such function.
str= str+*i+ (int) (*j)
=”c-pointer.blogspot.com” + *&a+ (int) (*&b)
//i=&a, j=&b
=”c-pointer.blogspot.com” + a+ (int) (b)
=”c-pointer.blogspot.com” +2 + (int) (2.0)
=”c-pointer.blogspot.com” +4
=”inter.blogspot.com”

(4) What will be output if you will execute following code?
char far * display(char far*);
int main()
{
	char far* string="cquestionbank.blogspot.com";
	char far *(*ptr)(char far *);
	ptr=&display;
	string=(*ptr)(string);
	printf("%s",string);
}
char far *display(char far * str)
{
	char far * temp=str;
	temp=temp+13;
	*temp='\0';
	return str;
}

Output: cquestionbak
Explanation: Here display is function whose parameter is pointer to character and return type is also pointer to character and ptr is its pointer.

temp is char pointer
temp=temp+13
temp=’\0’

Above two lines replaces first dot character by null character of string of variable string i.e.
"cquestionbank\0blogspot.com"

As we know %s print the character of stream up to null character.
*/
