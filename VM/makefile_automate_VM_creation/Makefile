# The idea is to have a Makefile that does all the needed steps to have runnable VM in  virt-manager

all:
	# installing the needed packages, just in case
	sudo apt-get install uvtool
	# downloading ubuntu images
	uvt-simplestreams-libvirt sync arch=amd64
	# checking what has been downloaded 
	uvt-simplestreams-libvirt query
	# create the VM
	uvt-kvm create --password=ubuntu  auto_uvtool release=utopic arch=amd64
