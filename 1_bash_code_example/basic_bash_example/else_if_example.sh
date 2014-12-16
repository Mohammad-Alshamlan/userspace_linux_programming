#!/bin/bash

	# start with clearing the screen is better
	clear

	# giving the user message to let them what to do
	echo -n -e "Enter a Number:\t"
	# read user input and store it in num variable
	read num

	#after inputting, is better to clear the screen again
	clear

	# declare the if statement
	if [ "$num" -eq 10 ]
	# start the if statment
	then 
	# the function body of the if statement
	echo "you chose 10"
	# using else if
	elif [ "$num" -eq 11 ]
	# begin else if
	then
	# else if body code
	echo "11 is bigger than 10, but it's still not 10!!"
	# declaring another else if condition
	elif [ "$num" -eq 9 ]
	# start using it
	then 
	# the body of the second else if
	echo "9 is smaller than 10, but it's still not 10!!"
	# using else
	else
	echo "choose 10"
	# end the if statement with "fi"
	fi 
