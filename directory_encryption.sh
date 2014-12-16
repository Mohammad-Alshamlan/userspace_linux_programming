#!/bin/bash

function is_the_needed_software_installed()
{
	# we sill check through bash core dump
	which encfs
	if [ $? == 1 ]
	then 
		echo -e "we need to install encfs"
		sudo apt-get update && sudo apt-get -y install encfs
	fi
	
}

function decrypting_directory()
{
	mkdir -p note
	encfs ${PWD}/.note/ ${PWD}/note/
}

function unmount_the_decrypted_directory()
{
	# unmout the directory
	fusermount -u ${PWD}/note
	
}
#
case "${1}" in 
	start|"")
		echo -e "start is selected!!"
		# check if the needed software are there
		is_the_needed_software_installed
		# decrypting the encripted directory
		decrypting_directory
	;;
	
	stop)
		echo -e "stop is selected!!"
		# unmount the decrypted directory
		unmount_the_decrypted_directory
	;;
	
	*)
		echo -e "Usage: $0 {start|stop}" >&2
		exit 1
	;;
esac
	
