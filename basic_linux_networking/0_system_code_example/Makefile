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
all: $(OBJ)

$(OBJ): 
	$(CC) $(CFLAGS) $@ -o $(@:%.c=%)

clean:
	$(RM) $(OBJ:%.c=%) *~

