################################
# makefile settings	       #
# version: Nov25_2014	       #
################################
SHELL := /bin/bash
CC=gcc
CFLAGS += -g -Wall -MD -MP
RM := $(shell which rm)
RM += -f 
OBJ = $(wildcard *.c)
################################
# generic makefile for c code  #
################################
all: $(OBJ)

$(OBJ): 
	$(CC) $(CFLAGS) $@ -o $(@:%.c=%)

#The include directive must list the dependency files. Most makefiles will already have a list of source or object files, from which the names of the dependency files can be obtained by substitution. In this particular example it is possible to use the variable SRC which is a list of source files:
-include $(OBJ:%.c=%.d)
#The purpose of the initial hyphen is to suppress the error messages that would otherwise appear when the dependency files do not already exist.

clean:
	$(RM) $(OBJ:%.c=%) $(OBJ:%.c=%.d) *~

