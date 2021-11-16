/*
 * test_thread_conditional_monitor.c
 *
 * This file illustrates the use of conditional monitor to
 * guard access to a resource with pthreads in C. When two
 * threads share same memory, use monitor to make it safe.
 * Also guarantees that memory values between different CPU
 * cores are synchronized.
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

/**
 * Monitor for message string.
 * Simplest way to create monitor, no function calls needed.
 */
pthread_mutex_t message_lock = PTHREAD_MUTEX_INITIALIZER;

/**
 * Condition for message state changes.
 * Simplest way to create condition, no function calls needed.
 */
pthread_cond_t message_cond = PTHREAD_COND_INITIALIZER;

/** shared string resource */
char message[128] = "";  // no message

/**
 * This thread function consumes message strings.
 *
 * @return pointer-encoded count of messages consumed
 */
void *consumer(void *arg) {
	unsigned int msgcount = 0;
	fprintf(stderr, "    consumer: thread beginning\n");
	bool quit = false;

	// If producer has monitor, thread waits; when producer unlocks, thread continues
	fprintf(stderr, "    consumer: waiting for monitor lock\n");
	pthread_mutex_lock(&message_lock);  // lock message monitor
		do {
			fprintf(stderr, "    consumer: monitor locked\n");
			if (strlen(message) == 0) {
				fprintf(stderr, "    consumer: waiting to receive next message\n");
				do {
					pthread_cond_wait(&message_cond, &message_lock);
				} while (strlen(message) == 0);
			}
			fprintf(stderr, "    consumer: received message is '%s'\n", message);
			quit = (strcmp(message, "quit") == 0);
			strcpy(message,"");
			pthread_cond_signal(&message_cond);  // signal message received
			msgcount++;
		} while (!quit);
		fprintf(stderr, "    consumer: unlocking monitor\n");
	pthread_mutex_unlock(&message_lock); // unlock message monitor

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
	pthread_mutex_lock(&message_lock); // lock message monitor
		while (msgindex < nmessages) {
			// wait for consumer
			if (strlen(message) != 0) {
				fprintf(stderr, "producer: waiting to send next message\n");
				do {
					pthread_cond_wait(&message_cond, &message_lock);
				} while (strlen(message) != 0);
			}

			// send next message
			fprintf(stderr, "producer: sending message '%s'\n", messages[msgindex]);
			strcpy(message, messages[msgindex++]);

			// signal message available
			pthread_cond_signal(&message_cond);
			sleep(2);  // to slow things down for demo purposes
		}
	pthread_mutex_unlock(&message_lock);  // unlock message monitor

	fprintf(stderr, "producer: ending\n");
}

/**
 * Creates consumer thread, runs producer, and reports results.
 */
int main(void) {
	pthread_t consumer_tid;  // thread for consumer

	// create and start consumer thread
	pthread_mutex_lock(&message_lock); // lock message monitor to block thread
		fprintf(stderr, "main: creating consumer\n");
		pthread_create(&consumer_tid, NULL, consumer, NULL);
		sleep(2);  // to slow things down
	pthread_mutex_unlock(&message_lock);  // unlock monitor

	// produce messages
	const char* messages[] = {"first", "second", "third", "quit"};
	producer(4, messages);

	// wait for consumer and report count
	void *msgcount;
	pthread_join(consumer_tid, &msgcount);
	fprintf(stderr, "main: finished with msgcount %u\n", (unsigned)((char*)msgcount - (char*)0));
}
