# The idea is to create a makefile variable, and then to output this makefile variable onto sub-bash process
Makefile_var="This is a hello from Makefile"

SHELL := /bin/bash

.PHONY: all NotWorking
all:
	# creating make variable at rule execution time isn't stratforward
	$(eval export bash_var="this is a hello from Bash")	# this is a must to create a variable inside the target!! 
	echo ${bash_var} ${Makefile_var}  # both will show on the output
	
NotWorking:
	export export bash_var="this is a hello from Bash"
	echo ${bash_var} ${Makefile_var} # only ${Makefile_var} will output, and not ${bash_var}

DesentWorking:
	( eval export bash_var="this is a hello from Bash" && echo ${bash_var} ${Makefile_var} )
	echo ${bash_var} ${Makefile_var} 
