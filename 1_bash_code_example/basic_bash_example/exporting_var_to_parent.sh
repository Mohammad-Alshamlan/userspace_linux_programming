#!/bin/bash

# when you run a script is run on the sub-shell. So, when the subshell finishes, the sub-shell dies without sharing the variables with the partent

# Example of the problem
#	alshamlan@alshamlan-K55A:/tmp/interview$ cat -n q1.sh 
#	     1	#!/bin/bash
#	     2	export CHECK="exist!!"
#	     3	echo ${CHECK}
#	alshamlan@alshamlan-K55A:/tmp/interview$ bash q1.sh 
#	exist!!
#	alshamlan@alshamlan-K55A:/tmp/interview$ echo $CHECK
#
#	alshamlan@alshamlan-K55A:/tmp/interview$ 

# soultion: running the script with source!!
# Example for the soultion

#	alshamlan@alshamlan-K55A:/tmp/interview$ cat -n q1.sh 
#	     1	#!/bin/bash
#	     2	export CHECK="exist!!"
#	     3	echo ${CHECK}
#	alshamlan@alshamlan-K55A:/tmp/interview$ source q1.sh 
#	exist!!
#	alshamlan@alshamlan-K55A:/tmp/interview$ echo $CHECK 
#	exist!!
#	alshamlan@alshamlan-K55A:/tmp/interview$ 

export CHECK="exist!!"
echo ${CHECK}

