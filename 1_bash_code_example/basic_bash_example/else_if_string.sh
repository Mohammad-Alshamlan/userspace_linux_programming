#!/bin/bash

clear # just making the script nicer
# name IO 
echo -n -e "Enter Your Name:\t"
read name

# Clearing name IO 
clear
# starting if statement with fixing case sentative
if [ "${name,,}" = "kris" ] # you can see clearly that string if condition is different than integer where was "if [ "$name" -eq 10]"
then 
# the body of if statement 
	echo "Hi, $name"
# using else if with fixing case sentativeness
elif [ "${name,,}" = "tim" ]
then
# the body of else if statement
	echo "what's $name" 
# having the else statement
else 
	echo -e "Look man, I don't know you!!\nUse one of these: \n\t[1]kris\n\t[2]tim"

fi
