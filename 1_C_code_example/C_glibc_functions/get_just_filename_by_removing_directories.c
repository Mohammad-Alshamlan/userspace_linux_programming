/*
 * Idea is to just to extact the filename from the pathname with basename
 * 
 * Example, 
 * 	(bash) $ ./get_just_filename_by_removing_directories /tmp/some_file/file.txt
 *		filename:	file.txt
 *		path:		/tmp/some_file
 *
 * 	(bash) $ ./get_just_filename_by_removing_directories 
 *		Please, run it as follows:
 *			(bash) $ ./get_just_filename_by_removing_directories <pathname>
 *
 * 	(bash) $ ./get_just_filename_by_removing_directories somefile.txt 
 *	filename:	somefile.txt
 *	path:		.
 *
 */
 
#include<libgen.h>
#include<stdio.h>

int main(int argc, char *argv[])
{
	// check if the program has run with the right number of arguments
	if (argc < 2){
		fprintf(stderr,"Please, run it as follows:\n\t(bash) $ %s <pathname>\n", argv[0]);
		return 1;
	}
	// now let show the filename 
	printf("filename:\t%s\n", basename(argv[1]));
	// now let show the extracted directories from the pathname
	printf("path:\t%s\n", dirname(argv[1]));
	// done!!
	return 0; 
}
