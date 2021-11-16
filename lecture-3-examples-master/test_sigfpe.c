/*
 * test_sigfpe.c
 *
 *  Created on: Jul 23, 2018
 *      Author: philip gust
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/** Handler for SIGFPE signal */
void SIGFPE_handler(int sig) {
	printf("received SIGFPE\n");
	exit(EXIT_FAILURE);
}

int main() {
	// register the SIGFPE handler
	signal(SIGFPE, SIGFPE_handler);

	// divide by 0.0
	int x = 3;
	int y = 0;

	printf("dividing %d by %d\n", x, y);
	int fpe = x/y;

	printf("value of dividing %d by %d is %d\n", x, y, fpe);

	return EXIT_SUCCESS;
}

