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
run_tcp_daytime_server:
	# note, I wasn't able to run it as a reguler user!!
	sudo ncat -l 13 --send-only --exec "/bin/date"

clean:
	$(RM) $(OBJ) 
	# deleting the temp hiden saving files
	$(RM) *~
