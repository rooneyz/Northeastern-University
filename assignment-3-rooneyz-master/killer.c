/*
 * killer.c
 *
 *  Created on: May 24, 2019
 *      Author: zachrooney
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

 // The process id
static pid_t pid;

// Other process id
static pid_t otherPID;

// Menu Choice
int menuChoice;s

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
 * Handle SIGCONT as notification that the process is continuing. Reprints
 * the menu options
 */
void SIGCONT_handler(int sig) {
	printf("Received SIGCONT: resuming\n");
	printf("Please Choose A Signal\n");
	printf(" 0) QUIT\n 1) SIGSTP\n 2) SIGCONT\n 3) SIGTERM\n 4) SIGUSR1\n 5) SIGUSR2\n");

}

/**
 * Handle SIGTERM as request to terminate the process normally.
 * Similar to SIGKILL but enables application to intercept and
 * handle the signal.  This handler calls exit()
 */
void SIGTERM_handler(int sig) {
	printf("Received SIGTERM: terminating normally\n");
    exit(EXIT_SUCCESS);
}

/**
 * Handle SIGUSR1, an application specific signal. This handler
 * prints the current process id
 */
void SIGUSR1_handler(int sig) {
	printf("Received SIGUSR1: Current process id: %d\n", pid);
}

/**
 * Handle SIGUSR2, an application specific signal. This handler
 * prints the 'other' process id (process entered by the user)
 */
void SIGUSR2_handler(int sig) {
	printf("Received SIGUSR2: Other process id: %d\n", otherPID);
}

int main() {
   // Register signal and signal handler
   signal(SIGTSTP, SIGTSTP_handler);
   signal(SIGCONT, SIGCONT_handler);
   signal(SIGTERM, SIGTERM_handler);
   signal(SIGUSR1, SIGUSR1_handler);
   signal(SIGUSR2, SIGUSR2_handler);


   // Get the process id
   pid = getpid();

   printf("Current process id: %d \n" , pid);
   printf("Please input a PID: \n");

   // Get user input for otherPID
   scanf("%d", &otherPID);
   printf("You entered: %d\n", otherPID);

   // Menu loop
   while(running) {
      printf("%d: hello from process id %d\n", ++count, pid);
      printf("Please Choose A Signal\n");
      printf(" 0) QUIT\n 1) SIGSTP\n 2) SIGCONT\n 3) SIGTERM\n 4) SIGUSR1\n 5) SIGUSR2\n");
      menuChoice = -1;
      scanf("%d", &menuChoice);
      setbuf(stdin, NULL);
      switch (menuChoice)
      {
      	  case 0:  running = false;
      	      break;
      	  case 1: if ((kill(otherPID, SIGTSTP)) == -1){
      		  printf("Process %d no longer available\n", otherPID);
      		  running = false; }
              break;
          case 2: if (kill(otherPID, SIGCONT) == -1){
      		  printf("Process %d no longer available\n", otherPID);
      		  running = false; }
        	  break;
          case 3: if (kill(otherPID, SIGTERM) == -1){
      		  printf("Process %d no longer available\n", otherPID);
      		  running = false; }
        	  break;
          case 4: if (kill(otherPID, SIGUSR1) == -1){
      		  printf("Process %d no longer available\n", otherPID);
      		  running = false; }
        	  break;
          case 5:if (kill(otherPID, SIGUSR2) == -1){
      		  printf("Process %d no longer available\n",  otherPID);
      		  running = false; }
        	  break;
          default: printf("Not a Valid Choice. Please Choose Again\n");
          	  break;
      }

   }
   return EXIT_SUCCESS;
}



