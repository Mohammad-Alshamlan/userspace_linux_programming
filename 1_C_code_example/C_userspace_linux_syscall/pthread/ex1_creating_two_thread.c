/*
 * creating to joinable threads
 * source: linux system programming 2nd Edition, page 234 (or 261 in PDF) 
 *
 * Example, how to compile this code
 *	(bash) $ gcc -Wall -pthread -g example.c -o example
 *
 * to-do-list:
 *	[1] below code lacks error-checks!!
 */

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *start_thread (void *message)
{
	// printf() is thread-safe, so it won't output gibberish text because of race condition!!
	printf("%s\n", (const char *) message);
	// done
	return message;
}

int main(int argc, char *argv[])
{
	pthread_t thread1, thread2;
	const char *message1= "Thing 1";
	const char *message2= "Thing 2";
	
	// Create two threads, each with a different message
	pthread_create (&thread1, NULL, start_thread, (void *) message1);
	pthread_create (&thread2, NULL, start_thread, (void *) message2);
	
	/* 
	 * wait for the threads to exit. If we didn't join here, 
	 * we'd risk terminating this main thread before the
	 * other two threads finished.
	 */ 
	pthread_join (thread1, NULL);
	pthread_join (thread2, NULL);
	
	return 0;
}
