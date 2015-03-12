/*
 * creating to joinable threads, and lock an element in mutex
 *
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
#include<string.h>
#include<pthread.h>

#ifndef STRING_LENGTH
#define STRING_LENGTH 32
#endif

#define CUSTOMER_BALANCE 1000
#define CUSTOMER_NAME "Eric"
#define WITHDRAW 800
// example of bank account structure
struct account{
	float balance;
	char name[STRING_LENGTH];
	pthread_mutex_t mutex;
};

// initalize mutex


// using mutex in this function
int withdraw (struct account *account, int amount)
{
	// debug trace
	printf("%u\t%s\t%f\t%d\n", pthread_self(), account->name, account->balance, amount);
	/*
	 * Most uses of locks avoid global locks and instead associate locks wth
	 * specific instances of data structures. This is called fine-grained locking. 
	 * It can make your locking semantics more complicated, particularly aroud 
	 * deadlock avoidance, but is key in scaling to the number of cores on modern machines
	 *
	 * In this example, instead of defining a global the_mutex lock, we define a mutex inside
	 * of the account structure, giving each account its own lock. This works wellas the data
	 * within the critical region is only the account structure. By locking only the account
	 * being debited, we allow the bank to process other customers' withdraws in parallel.
	 */
	pthread_mutex_lock (&account->mutex);
	const int balance = account->balance;
	if(balance < amount ) {
		pthread_mutex_unlock(&account->mutex);
		return -1;
	}
	account->balance = balance - amount;
	pthread_mutex_unlock (&account->mutex);
	//
	printf("cash out $%d\n", amount);
	//
	return 0;
}

void *start_thread (void *pass_data)
{
	// casting 
	struct account *customer = (struct account *) pass_data;
	// get the thread TID
	const pthread_t me = pthread_self();	
	// printf() is thread-safe, so it won't output gibberish text because of race condition!!
	printf("%u\t%s\t%f\n", me, customer->name, customer->balance);
	int rc = withdraw (customer, WITHDRAW);
	if(rc){
		fprintf(stderr, "can't withdraw $%d because the existent amount is $%f\n", WITHDRAW, customer->balance);
	}
	// done
	return pass_data;
}

int main(int argc, char *argv[])
{
	// creating two threads
	pthread_t thread1, thread2;

	// create a customer account
	struct account *customer = (struct account *) malloc (sizeof(struct account));
	if (customer == NULL ){
		perror("malloc failed!!");
		return 1;
	}
	// define the customer structure
	customer->balance=CUSTOMER_BALANCE;
	memset(customer->name, 0, STRING_LENGTH);
	strcpy(customer->name, CUSTOMER_NAME);
	// inialize the mutex
	//customer->mutex = PTHREAD_MUTEX_INITIALIZER;
	
	// Create two threads, each with a different message
	pthread_create (&thread1, NULL, start_thread, (void *) customer);
	pthread_create (&thread2, NULL, start_thread, (void *) customer);
	
	/* 
	 * wait for the threads to exit. If we didn't join here, 
	 * we'd risk terminating this main thread before the
	 * other two threads finished.
	 */ 
	pthread_join (thread1, NULL);
	pthread_join (thread2, NULL);
	
	// free the heap
	free(customer);
	
	return 0;
}
