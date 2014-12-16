#!/bin/bash

	# giving the user message to let them what to do
	echo -n -e "Enter a Number:\t"
	# read user input and store it in num variable
	read num

	# declare the if statement
	if [ "$num" -eq 10 ]
	# start the if statment
	then 
	# the function body of the if statement
	echo "you chose 10"
	# using else
	else
	echo "choose 10"
	# end the if statement with "fi"
	fi 
