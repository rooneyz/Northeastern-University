/*
 * test_sigfpe.c
 *
 *  Created on: Jul 23, 2018
 *      Author: philip gust
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/** Handler for SIGSEGV signal */
void SIGSEGV_handler(int sig) {
	printf("received SIGSEGV\n");
	exit(EXIT_FAILURE);
}

int main() {
	// register the SIGSEGV handler
	signal(SIGSEGV, SIGSEGV_handler);

	// Dereference null pointer
	char *ptr = NULL;
	printf("dereferencing %p\n", ptr);
	char ch = *ptr;

	printf("value of ch is %c\n", ch);

	return EXIT_SUCCESS;
}

