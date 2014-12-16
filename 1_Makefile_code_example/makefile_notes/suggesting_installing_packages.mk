# we want to use bash, so specify the used shell as bash
SHELL := /bin/bash
#see if COMMAND exists. If not, then set a defulat value such as "ls" command
ifeq (,$(COMMAND))
	export COMMAND := ls
endif
# let look for this command if it exists or not
COMMAND_EXISTENCE := $(shell which $(COMMAND) 2> /dev/null; echo $$?)
ifeq ($(COMMAND_EXISTENCE),1)
    $(error "you don't have "$(COMMAND)" command. Please install it and re-try!!")
endif

all:
	echo -e "use 'COMMAND' build variable to check if a commnad exists in your system or not!!\nFor example:\n\t(bash) make COMMAND=kjdnjjdj \n"

