export codeB_hello= "Hello from codeB makefile"

#.PHONY: all
all:
	echo "---------------------------"
	echo makefile codeB
	echo "---------------------------"
	echo WORKROOT: ${WORKROOT}
	echo WORKROOT_hello: ${WORKROOT_hello} 
	echo codeA_hello: ${codeA_hello} 
	echo codeB_hello: ${codeB_hello}
	echo codeC_hello: ${codeC_hello}
	# openning another make
	make -C ${WORKROOT}/codeC


