/*
 * test_signals.c
 *
 * This program demonstrates basic signal handling in a C program.
 *
 *  Created on: Jul 26, 2017
 *  Author: phil
 */
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#ifndef SIGINFO
#define SIGINFO 29
#endif

/** slow sleep time */
const int slow_sleep_time = 5;

/** fast sleep time */
const int fast_sleep_time = 1;

/** initial sleep time */
int sleep_time;

/** indicates process is running */
bool running = true;

/** count of output lines */
int count=0;


/**
 * Handle SIGTSTP as request to stop/suspend process. Similar to
 * SIGSTOP, but enables application to intercept and handle the
 * signal.  Typing CNTL-Z into a terminal sends SIGSTOP to the
 * process associated with the keyboard.
 */
void SIGTSTP_handler(int sig) {
	printf("Received SIGTSTP: suspending\n");
	pause();
}

/**
 * Handle SIGQUIT as request to suspend process. Similar to
 * SIGTERM but dumps program memory.  Typing  CNTL-\ into
 * terminal sends SIGQUIT to process associated with keyboard.
 */
void SIGQUIT_handler(int sig) {
	printf("Received SIGQUIT: suspending\n");
	raise(SIGSTOP);  // suspends process
}

/**
 * Handle SIGCONT as notification that the process is continuing.
 */
void SIGCONT_handler(int sig) {
	printf("Received SIGCONT: resuming\n");
}

/**
 * Handle SIGTERM as request to terminate the process normally.
 * Similar to SIGKILL but enables application to intercept and
 * handle the signal.  This handler Sets running to false and
 * waits for process to terminate.
 */
void SIGTERM_handler(int sig) {
	printf("Received SIGTERM: terminating normally\n");
	running = false;
}

/**
 * Handle SIGINT by resetting the line count. This interrupt
 * is described as interrupting the process, but what occurs
 * is application specific. Default SIGINT handler is the
 * same as the default handler for SIGTERM. Typing CNTL-C into
 * a terminal window sends SIGINT to the process associated with
 * the keyboard. This handler resets the displayed count.
 */
void SIGINT_handler(int sig) {
	printf("Received SIGINT: resetting count\n");
	count = 0;
}

/**
 * Handle SIGINFO, request for info about the program. This
 * handler prints the sleep time and count.
 */
void SIGINFO_handler(int sig) {
	printf("Received SIGINFO: sleep time: %d, count: %d\n", sleep_time, count);
}

/**
 * Handle SIGUSR1, an application specific signal. This handler
 * sets the sleep time to the slow sleep time
 */
void SIGUSR1_handler(int sig) {
	printf("Received SIGUSR1: setting slow sleep time\n");
	sleep_time = slow_sleep_time;
}

/**
 * Handle SIGUSR2, an application specific signal. This handler
 * set the sleep time to the fast sleep time.
 */
void SIGUSR2_handler(int sig) {
	printf("Received SIGUSR2: setting fast sleep time\n");
	sleep_time = fast_sleep_time;
}

int main() {
   // Register signal and signal handler
   signal(SIGTSTP, SIGTSTP_handler);
   signal(SIGQUIT, SIGQUIT_handler);
   signal(SIGCONT, SIGCONT_handler);
   signal(SIGTERM, SIGTERM_handler);
   signal(SIGINT,  SIGINT_handler);
   signal(SIGUSR1, SIGUSR1_handler);
   signal(SIGUSR2, SIGUSR2_handler);
   signal(SIGINFO, SIGINFO_handler);

   // The process id
   pid_t pid = getpid();

   sleep_time = slow_sleep_time;

   while(running) {
      printf("%d: hello from process id %d\n", ++count, pid);
      sleep(sleep_time);
   }
   return EXIT_SUCCESS;
}


