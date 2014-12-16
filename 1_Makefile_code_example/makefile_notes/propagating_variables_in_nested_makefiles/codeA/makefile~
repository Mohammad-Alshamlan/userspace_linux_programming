export codeA_hello="Hello from codeA makefile"

#.PHONY: all
all:
	echo "---------------------------"
	echo makefile codeA
	echo "---------------------------"
	echo WORKROOT: ${WORKROOT}
	echo WORKROOT_hello: ${WORKROOT_hello} 
	echo codeA_hello: ${codeA_hello} 
	echo codeB_hello: ${codeB_hello}
	echo codeC_hello: ${codeC_hello}
	# openning another make
	make -C $(WORKROOT)/codeA/codeB
	make -C ${WORKROOT}/codeC
	
	


