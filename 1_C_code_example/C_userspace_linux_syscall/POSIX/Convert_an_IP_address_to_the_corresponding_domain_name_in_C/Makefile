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

# rather than writing the client we can use ncat for our server testing!!
client:
	ncat `hostname` 5000 -t
	# for more verbosity add "-vv" option
	#ncat -vv `hostname` 5000 -t

clean:
	$(RM) $(OBJ) 
	# deleting the temp hiden saving files
	$(RM) *~
