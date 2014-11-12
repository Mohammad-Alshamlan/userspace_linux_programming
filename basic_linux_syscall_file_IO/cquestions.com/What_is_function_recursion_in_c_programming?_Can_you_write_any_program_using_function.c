/*
 * What is function recursion in c programming? Can you write any program using function?
 */

/*
Explanation:
Calling of same function from its function body is known as function recursion. It is alternative of loop. Any c program which is possible using loop it must be possible using function recursion. Simple example:
Find the sum of all even numbers from 0 to 20 using function recursion. Program:
*/
#include<stdio.h>
int main()
{
	int total;
	total=sum(2);
	printf("%d",total);
	return 0;
}
int sum(int i)
{
	static int even=0;
	if(i<=20){
		even=even+i;
		sum(i+2); //calling same function
	}
	return even;
}

/*
Output:
It is very difficult to understand the execution as well as to write the function recursion program.
How to write function recursion program in easier way:
I have already told it is very difficult to write function recursion program directly. If any person is writing such program directly he may be memorized that program. I am telling a very nice trick: how to write function recursion program in easier way?
As we know any c program which possible using loop it must be possible using function recursion.
Steps for how to write function recursion program:
Step1: First of all write same program using while loop and function. (Except main function)
Step 2: In that function make all local variable static.
Step 3: Replace while keyword by if.
Step 4: The increment or decrement of variable which is used for condition checking, replace with function call and pass the parameter of that incremented or decremented variable. Now understand by example:
Find the sum of all even numbers from 0 to 20 using function recursion.
Step 1: Write the same program using while loop and function. Here function is sum.

#include<stdio.h>
int main(){
int total;
total=sum(2);
printf("%d",total);
return 0;        
}
int sum(int i){
int even=0;
while(i<=20){
even=even+i;
i=i+2;
}
return even;
}

Step 2: Make local variable even as static variable

int sum(int i){
static int even=0;
while(i<=20){
even=even+i;
i=i+2;
}
return even;
}

Step 3: Replace while keyword by if keyword.

int sum(int i){
int even=0;
if(i<=20){
even=even+i;
i=i+2;
}
return even;
}

Step 4: Since here variable i has used in condition checking. So replace the statement i=i+2 by sum (i+2).

int sum(int i){
int even=0;
if(i<=20){
even=even+i;
sum(i+2);
}
return even;
}

Following only three simple change you can write any difficult function recursion program.

#include<stdio.h>
int main(){
int total;
total=sum(2);
printf("%d",total);
return 0;        
}
int sum(int i){
int even=0;
if(i<=20){
even=even+i;
sum(i+2);
}
return even;
}

One more example:
Write a program to find a factorial of given number using function recursion.
Step 1: write same program using while loop and function.

#include<stdio.h>
int main(){
int fact,num;
scanf("%d",&num);
fact=factorial(num);
printf("%d",fact);
return 0;        
}
int factorial(int num){
int fact=1; //make it static
while(num>0){ //replace while by if
fact=fact*num;
num--; // replace by function call as factorial(num-1);
}
return fact;
}

After following step1, step 2, step 3:

#include<stdio.h>
int main(){
int fact,num;
scanf("%d",&num);
fact=factorial(num);
printf("%d",fact);
return 0;        
}
int factorial(int num){
static int fact=1;
if(num>0){
fact=fact*num;
factorial (num-1);
}
return fact;
}

Note1: In step 3 while calling function don’t pass the parameter using unary operator like factorial (num--);
Note2: write the function in such a way parameter of calling function must be used in conditional statement. For example in the above program:

int factorial(int num)

num is function parameter and num is also used in the conditional if statement.
*/
