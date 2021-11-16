/*
 * test_sigusr1.c
 *
 *  Created on: Jul 23, 2018
 *      Author: philip gust
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/** Handler for SIGUSR1 signal */
void SIGUSR1_handler(int sig) {
	fprintf(stderr,"received SIGUSR1\n");
	fflush(stderr);
}

int main() {
	// register the SIGFPE handler
	signal(SIGUSR1, SIGUSR1_handler);

	// get id of this process
	pid_t pid = getpid();

	// send SIGUSR1 signal
	printf("sending SIGUSR1\n");
	kill(pid, SIGUSR1); // or raise(SIGUSR1);

	printf("sent SIGUSR1\n");
	return EXIT_SUCCESS;
}

