CFLAGS= -Wall -g -lpthread

ifneq (,$(SSH_ON))
	# I could not setup the below command, I got an error!!
	#touch ${INSTALL_MOD_PATH}/etc/SSH_ON
	TEXT="Okay, SSH_ON is selected"
endif

# make sure that SSH_ON is just two options and there is no other option.
# also make sure that the defult option is SSH_ON enable
ifneq ($(SSH_ON), enable)
ifneq ($(SSH_ON), disable)
	TEXT="reset to enable!!"
endif
endif


all:
	cc q1.c -o q1.o $(CFLAGS)
	echo $(TEXT)
	
# output
#	alshamlan@alshamlan-OptiPlex-980:/tmp/interview$ make -B all q1.c 
#	cc q1.c -o q1.o -Wall -g -lpthread
#	echo "reset to enable!!"
#	reset to enable!!
#	make: Nothing to be done for `q1.c'.
#
#	alshamlan@alshamlan-OptiPlex-980:/tmp/interview$ make -B all q1.c SSH_ON=disable
#	cc q1.c -o q1.o -Wall -g -lpthread
#	echo "Okay, SSH_ON is selected"
#	Okay, SSH_ON is selected
#	make: Nothing to be done for `q1.c'.
#
#	alshamlan@alshamlan-OptiPlex-980:/tmp/interview$ make -B all q1.c SSH_ON=enable
#	cc q1.c -o q1.o -Wall -g -lpthread
#	echo "Okay, SSH_ON is selected"
#	Okay, SSH_ON is selected
#	make: Nothing to be done for `q1.c'.
#	alshamlan@alshamlan-OptiPlex-980:/tmp/interview$ make -B all q1.c SSH_ON=enablei
#	cc q1.c -o q1.o -Wall -g -lpthread
#	echo "reset to enable!!"
#	reset to enable!!
#	make: Nothing to be done for `q1.c'.
#	alshamlan@alshamlan-OptiPlex-980:/tmp/interview$
