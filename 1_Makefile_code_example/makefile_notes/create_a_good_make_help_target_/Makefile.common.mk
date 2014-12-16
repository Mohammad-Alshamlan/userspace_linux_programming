# we want to use bash, so specify the used shell as bash
SHELL := /bin/bash
############################################
## help target
############################################
#check if 'view' command exists in the buildsystem. 
# if not, the use less!!
COMMAND_EXISTENCE := $(shell which view 2> /dev/null; echo $$?)
ifeq ($(COMMAND_EXISTENCE),1)
	export HELP_VIEWER := less
else
	export HELP_VIEWER := view
endif


