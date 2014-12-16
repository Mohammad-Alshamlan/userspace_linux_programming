# using bash env variable in a condition!! 

TEXT="testing the code"

ifneq (,$(SSH_ON))
	TEXT = " the condition is enable" 
endif

all: 
	echo ${TEXT}
	
# output trace
#	alshamlan@alshamlan-OptiPlex-980:~/Google Drive/Skillset/1_make/code_example/env_bash_condition$ make 
#	echo "testing the code"
#	testing the code
#	alshamlan@alshamlan-OptiPlex-980:~/Google Drive/Skillset/1_make/code_example/env_bash_condition$ make SSH_ON=1
#	echo " the condition is enable" 
#	 the condition is enable
#	alshamlan@alshamlan-OptiPlex-980:~/Google Drive/Skillset/1_make/code_example/env_bash_condition$ make SSH_ON
#	make: *** No rule to make target `SSH_ON'.  Stop.
#	alshamlan@alshamlan-OptiPlex-980:~/Google Drive/Skillset/1_make/code_example/env_bash_condition$ 





