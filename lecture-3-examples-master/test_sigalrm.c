/*
 * test_sigalrm.c
 *
 *  Created on: Apr 2, 2018
 *      Author: philip gust
 */
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/** waiting for alarm */
bool waiting = true;

/** Handler for SIGALRM */
void SIGALRM_handler(int sig) {
	fprintf(stderr, "time is up!\n");
	fflush(stderr);
	waiting = false;
}

int main() {
	// register SIGALRM handler
	signal(SIGALRM, SIGALRM_handler);

	// set up 1-second alarm
	alarm(1);

	// wait for alarm to go off
	while(waiting) {
		printf("waiting…\n");
	}
	printf("done waiting\n");
    return EXIT_SUCCESS;
}

