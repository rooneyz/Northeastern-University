/*
 * final-5.c
 *
 * A group of hungry students are having their meals together
 * while studying. Each has a certain number of meal tickets.
 *
 * Each student studies for a while, and then eats for a while,
 * repeating this until the meal tickets are used up and the
 * student leaves.
 *
 * The students are seated at a round table, and there is a
 * fork between each place. To eat, a student needs the fork
 * on the left and the right. If one of the forks is being
 * used by another student, the student waits for it to become
 * available. When done eating, the student puts down the right
 * and left fork and goes back to studying.
 *
 * The main method creates the students and their utensils,
 * and runs each student in a thread. Then it waits for threads
 * to complete when the students are out of meal tickets.
 *
 * An action function simulates a student action by printing
 * the student name and action being performed, then sleeping
 * for a period.
 *
 * You will implement the two main actions performed by each
 * student: study() and eat(). See the description of the two
 * actions for details.
 *
 * The forks are shared resources between neighboring students.
 * They are represented by semaphores that guard a critical
 * section where the student eats.
 *
 * The accompanying "final-5_out.txt" file shows sample
 * output. Actual output may vary due to thread scheduling
 * differences.
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "semaphore.h"

// use three students
#define N_STUDENTS 3

// each student gets tickets for three meals
#define N_MEAL_TICKETS 3



/**
 * Hungry student has a name, a ticket for some meals, and
 * left and right forks shared with neighbors. Student needs
 * both forks to eat, and must wait until both are available.
 */
typedef struct  {
	/** Student id */
	int id;

	/** Number of meal tickets */
	int mealTicketCount;

	/** Left fork (represented by semaphore) */
	sem_t leftFork;

	/** Right fork (represented by semaphore) */
	sem_t rightFork;
} HungryStudent;

/**
 * Simulate a student action that takes some time by printing the
 * student name and description, and sleeping a random time period.
 *
 * @param student the student performing the action
 * @param description a description of the action
 */
void action(HungryStudent* student, const char* description)  {
	printf("Student %d: %s\n", student->id, description);
	sleep(random() % 2);  // random sleep
}

/**
 * Student action to study for a period of time.
 *
 * @param student the student performing the action
 */
void study(HungryStudent* student) {
	action(student, "study");
}

/**
 * Student action to eat for a period of time.
 *
 * Left and right forks are shared with neighbors. Student needs
 * both forks to eat, and must wait until both are available.
 *
 * To eat, student first picks up the left fork, then the right
 * fork, then eats. When done, student first puts down first the
 * right fork  then left fork, then decrements the meal ticket.
 *
 * @param student the student performing the action
 */
void eat(HungryStudent* student) {
	// wait to pick up the left fork
	sem_wait(&student->leftFork);
		action(student, "pick up left fork");

		// wait to pick up the right fork
		sem_wait(&student->rightFork);
			// eat for a while with both forks
			action(student, "pick up right fork");
			action(student, "eat");
			action(student, "put down right fork");
		sem_post(&student->rightFork);

		action(student, "put down left fork");

		// punch the student's meal ticket
		student->mealTicketCount--;
	sem_post(&student->leftFork);
}


/**
 * Function run by a student thread.
 *
 * @param arg pointer to the HungryStudent for this thread
 */
void *run(void *arg) {
	HungryStudent *student = (HungryStudent*)arg;

	// student studies and eats while meal tickets available
	while (student->mealTicketCount > 0) {
		study(student);
		eat(student);
	}

	printf("Student %d: meal ticket expired\n", student->id);

	// nothing returned
	return NULL;
}

/**
 * Creates students, fork semaphores, and thread resources
 * for N_STUDENTS with N_MEAL_TICKETS.
 */
int main() {
	setlinebuf(stdout); // buffer lines
	printf("Start final-5\n");

	// initialize semaphores as forks for students
	sem_t forks[N_STUDENTS];
	for (int i = 0; i < N_STUDENTS; i++) {
		sem_init(&forks[i], 0, 1);
	}

	// storage for students and threads
	HungryStudent students[N_STUDENTS];
	pthread_t student_threads[N_STUDENTS];

	// initialize students and run students in threads
	for (int id = 0; id < N_STUDENTS; id++) {
		// set number of student meal tickets
		students[id].mealTicketCount = N_MEAL_TICKETS;

		// set student id
		students[id].id = id;

		// set semaphores as left and right forks for students
		sem_t leftFork = forks[id];
		sem_t rightFork = forks[(id+1)%N_STUDENTS];

		if (id == 0) {
			// cross-over forks for first student to avoid deadlock
			students[id].leftFork = rightFork;
			students[id].rightFork = leftFork;
		} else {
			// set left and right forks normally for other students
			students[id].leftFork = leftFork;
			students[id].rightFork = rightFork;
		}

		// run student in thread
		pthread_create(&student_threads[id], NULL, run, &students[id]);
	}

	// wait for student threads to complete
	for (int i = 0; i < N_STUDENTS; i++) {
		pthread_join(student_threads[i], NULL);
	}

	printf("End final-5\n");
}
