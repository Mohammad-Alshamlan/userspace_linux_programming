################################
# makefile settings	       #
################################
CC=gcc
CFLAGS= -g -Wall
rm=$(which rm)
# the building objects
OBJ  = ex1_basic_read_syscall
OBJ += ex2_basic_lseek_syscall

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
