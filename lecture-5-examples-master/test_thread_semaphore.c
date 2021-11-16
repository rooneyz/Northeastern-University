/*
 * test_thread_semaphore.c
 *
 * This file illustrates the use of monitor to guard access to
 *  a resource with pthreads in C. When two threads share same
 * memory, use monitor to make it safe. Also guarantees that
 * memory values between different CPU cores are synchronized.
 *
 *  @since: 2018-04-08
 *  @author philip Gust
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "semaphore.h"

/** mutual exclusion semaphore */
sem_t semaphore;

/** shared string resource */
char message[128] = "";  // no message

/**
 * This function is run by a thread.
 */
void *consumer(void *arg) {
	unsigned int msgcount = 0;
	bool quit = false;

	fprintf(stderr, "    consumer: thread beginning\n");

	do {
		fprintf(stderr, "    consumer: waiting to lock semaphore\n");
		// If producer has monitor, thread waits; when monitor unlocks, thread continues
		sem_wait(&semaphore);  // lock critical section
			fprintf(stderr, "    consumer: locked semaphore\n");
			if (strlen(message) > 0) {  // message available
				// report and truncate message
				fprintf(stderr, "    consumer: consuming message '%s'\n", message);
				quit = (strcmp(message, "quit") == 0);
				strcpy(message,"");
				msgcount++;
			} else {  // no message yet
				fprintf(stderr, "    consumer: waiting for next message to consume\n");
			}
			fprintf(stderr, "    consumer: unlocking semaphore\n");
		sem_post(&semaphore);  // unlock critical section
		sleep(1);  // sleep to give producer time to produce message
	} while (!quit);

	fprintf(stderr, "    consumer: thread finishing\n");
	return ((char*)0 + msgcount);  // pointer encoded count
}

/**
 * This function produces message strings.
 *
 * @param nmessages number of messages
 * @param messages messages to produce
 */
void producer(int nmessages, const char *messages[]) {
	unsigned msgindex = 0;

	fprintf(stderr, "producer: beginning\n");

	while (msgindex < nmessages) {
		fprintf(stderr, "producer: waiting to lock semaphore\n");
		sem_wait(&semaphore);  // lock critical section
			fprintf(stderr, "producer: locked semaphore\n");
			if (strlen(message) == 0) {  // message was consumed
				fprintf(stderr, "producer: producing message '%s'\n", messages[msgindex]);
				strcpy(message, messages[msgindex++]);
			} else {  // message not yet consumed
				fprintf(stderr, "producer: waiting to produce next message\n");
			}
			fprintf(stderr, "producer: unlocking semaphore\n");
		sem_post(&semaphore);  // unlock critical section
		sleep(3);  // sleep to give consumer time to consume message
	}

	fprintf(stderr, "producer: ending\n");
}

/**
 * Creates consumer thread, runs producer, and reports results.
 */
int main(void) {
	pthread_t consumer_tid;  // thread for consumer

	// initialize semaphore
    if (sem_init(&semaphore, 0, 1) != 0) {
    	perror("sem_init");
    	return EXIT_FAILURE;
    }

    // create and start consumer thread
	sem_wait(&semaphore);  // lock critical section
		fprintf(stderr, "main: creating consumer\n");
		pthread_create(&consumer_tid, NULL, consumer, NULL);
		sleep(2);  // to slow things down
	sem_post(&semaphore);  // unlock critical section

	// produce messages
	const char* messages[] = {"first", "second", "third", "quit"};
	producer(4, messages);

	// wait for consumer and report count
	void* msgcount;
	pthread_join(consumer_tid, &msgcount);
	fprintf(stderr, "main: finished with msgcount %u\n", (unsigned)((char*)msgcount - (char*)0));
}
