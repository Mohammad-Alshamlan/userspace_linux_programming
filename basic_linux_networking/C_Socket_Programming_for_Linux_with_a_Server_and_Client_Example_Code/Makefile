################################
# makefile settings	       #
################################
SHELL := /bin/bash
CC=gcc
CFLAGS= -g -Wall
RM := $(shell which rm)
RM += -f 
OBJ := $(shell (ls *.c | cut -d'.' --complement -f2-))
################################
# generic makefile for c code  #
################################
all: $(OBJ)

$(OBJ): 
	$(CC) $(CFLAGS) $@.c -o $@ 

clean:
	$(RM) $(OBJ) 
	# deleting the temp hiden saving files
	$(RM) *~
