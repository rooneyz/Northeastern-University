/*
 * test_kill.c
 *
 *  Created on: Apr 2, 2018
 *      Author: phil
 */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/** Handler for SIGUSR1 signal */
void SIGUSR1_handler(int sig) {
	fprintf(stderr, "received SIGUSR1\n");
	fflush(stderr);
}

int main() {
	// register the SIGUSR1 handler
	signal(SIGUSR1, SIGUSR1_handler);

	// get id of this process
	pid_t pid = getpid();

	// send SIGUSR1 signal to this process
	printf("sending SIGUSR1\n");
	kill(pid, SIGUSR1);
	printf("sent SIGUSR1\n");

	return EXIT_SUCCESS;
}

