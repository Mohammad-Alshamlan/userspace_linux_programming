export WORKROOT=$(PWD)# note put "#" to prevent space #export will makefile variables pass down the other makefile
# for example: this "export WORKROOT=$(PWD) #" will break the build!!
export WORKROOT_hello="Hello from WORKROOT makefile"

#.PHONY: all
all: 
	echo "---------------------------"
	echo makefile WORKROOT
	echo "---------------------------"
	echo WORKROOT: ${WORKROOT}
	echo WORKROOT_hello: ${WORKROOT_hello} 
	echo codeA_hello: ${codeA_hello} 
	echo codeB_hello: ${codeB_hello}
	echo codeC_hello: ${codeC_hello}
	# invocaing anther make
	make -C $(WORKROOT)/codeA
	make -C $(WORKROOT)/codeC	


