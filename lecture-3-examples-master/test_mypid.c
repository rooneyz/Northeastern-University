/*
 * test_mypid.c
 *
 *  Created on: Mar 20, 2019
 *      Author: phil
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
	// get this process id
	pid_t mypid = getpid();
	printf("my process id is %d\n", mypid);

	// get parent process id
	pid_t myppid = getppid();
	printf("my parent process id is %d\n", myppid);
}
