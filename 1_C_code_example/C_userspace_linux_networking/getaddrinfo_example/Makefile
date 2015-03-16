################################
# makefile settings	       #
# version: Nov25_2014	       #
################################
SHELL := /bin/bash
CC=gcc
CFLAGS += -g -Wall
RM := $(shell which rm)
RM += -f 
OBJ = $(wildcard *.c)
################################
# generic makefile for c code  #
################################
.PHONY: all $(OBJ)

all: $(OBJ)

$(OBJ): 
	$(CC) $(CFLAGS) $@ -o $(@:%.c=%)
	@# let modify .gitignore if there is a new compiled executable
	@if [ "$(shell grep $(@:%.c=%) .gitignore)" != "$(@:%.c=%)" ];	\
	then								\
		echo $(@:%.c=%) >> .gitignore;				\
	fi

clean:
	$(RM) $(OBJ:%.c=%) *~

distclean: clean
