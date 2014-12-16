CFLAGS= -Wall -g -lpthread


# make sure that SSH_ON is just two options and there is no other option.
# also make sure that the defult option is SSH_ON enable
ifneq ($(SSH_ON), enable)
ifneq ($(SSH_ON), disable)
	SSH_ON="disable"
endif
endif


all:
	#cc q1.c -o q1.o $(CFLAGS)
	echo $(SSH_ON)
	
# output
#	alshamlan@alshamlan-OptiPlex-980:~/Dropbox/Skillset_for_dropbox_May31_2014/1_make/code_example/env_bash_condition_v3_resetting_if_needed$ make 
#	#cc q1.c -o q1.o -Wall -g -lpthread
#	echo "disable"
#	disable

#	alshamlan@alshamlan-OptiPlex-980:~/Dropbox/Skillset_for_dropbox_May31_2014/1_make/code_example/env_bash_condition_v3_resetting_if_needed$ make SSH_ON=enable
#	#cc q1.c -o q1.o -Wall -g -lpthread
#	echo enable
#	enable

#	alshamlan@alshamlan-OptiPlex-980:~/Dropbox/Skillset_for_dropbox_May31_2014/1_make/code_example/env_bash_condition_v3_resetting_if_needed$ make SSH_ON=disable
	#cc q1.c -o q1.o -Wall -g -lpthread
#	echo disable
#	disable

#	alshamlan@alshamlan-OptiPlex-980:~/Dropbox/Skillset_for_dropbox_May31_2014/1_make/code_example/env_bash_condition_v3_resetting_if_needed$ 
