################################
# makefile settings	       #
################################
CC=gcc
CFLAGS= -g -Wall
rm=$(which rm)
# the building objects
OBJ  = ex1_basic_read_syscall
OBJ += ex2_basic_lseek_syscall
OBJ += ex3a_binary_search
OBJ += ex3b_basic_lseek_syscall_binary_search
OBJ += ex3c_basic_pread_syscall_binary_searc
OBJ += ex4a_basic_scatter_input_readv_syscall
OBJ += ex5a_create_concatenated_positional_words
OBJ += ex5b_search_for_the_biggest_word
OBJ += ex5c_getting_the_file_descriptor_from_a_stream
OBJ += ex5d_search_for_the_biggest_word_simplified
OBJ += ex5e_show_all_number_combinations
OBJ += ex5f_double_linkedlist
OBJ += ex5g_sorted_linked_list
OBJ += ex5i_show_all_combinations_from_a_file_word_length
OBJ += ex5j_detect_biggest_words
OBJ += ex5z_all_possible_sting_concatenation_that_do_not_exceed_the_maximum_detected_string_size
OBJ += ex6a_compressing_a_file_with_zlib

################################
# generic makefile for c code  #
################################
all: $(OBJ)

$(OBJ): 
	$(CC) $(CFLAGS) $@.c -o $@ -lz

clean:
	$(RM) $(OBJ) 
	# deleting the temp hiden saving files
	$(RM) *~
