/*
 * final-4.c
 *
 * This program simulates a library and a set borrowers.
 * Each borrower borrows one book at a time, reads it
 * until the loan period ends, and then returns the book
 * to the library.
 *
 * The problem is to implement the borrower borrowBook()
 * and returnBook() functions that are called from the
 * borrower run() thread function. Complete descriptions
 * of the algorithms and messages produced by the methods
 * are in the method comment blocks.
 *
 * The accompanying "final-4_out.txt" file shows sample
 * output. Actual output may vary due to thread scheduling
 * differences.
 *
 * Note: requires C-11 complier dialect.
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

/** size of string buffer for output */
#define MAXBUF 128

/** number of borrowers */
#define N_BORROWERS 4

/** number of library in library */
#define N_BOOKS 3

/** values for book state */
typedef enum { checked_in, borrowed} BookState;

/**
 * library is array of books in a library; a book is
 * indicated by its index and its state by its value:
 * borrowed if borrowed,  checked_in if checked in.
 */
BookState library[N_BOOKS];

/** indicator of no book */
#define NO_BOOK -1

/** book circulation period */
#define CIRCULATION_PERIOD  2

/** library closing time */
#define CLOSING_TIME 7

/**
 * Mutex for library.
 * Simplest way to create monitor, no function calls needed.
 */
pthread_mutex_t library_mutex = PTHREAD_MUTEX_INITIALIZER;

/** Borrower record */
typedef struct {
	int id;  			/** the borrower ID */
	int book;     		/** checked out book */
	int due_by;         /** due by time for the book */
	int current_time;   /** the current simulated time */
	int borrowed_count; /** the number borrow operations */
} Borrower;

/**
 * Recommend a book to borrow. To ensure the book
 * remains available to borrow, access to this function
 * must be locked by the library_mutex.
 *
 * @return a recommended book
 */
int recommendBook() {
	for (int book = 0; book < N_BOOKS; book++) {
		if (library[book] == checked_in) {
			return book;
		}
	}
	return NO_BOOK;
}

/**
 * Set state of book to borrowed or checked_in.
 * @param book the book
 * @param state the state of the book
 * @return true if state changed
 */
bool setBookState(int book, BookState state) {
	if (book >= 0 && book < N_BOOKS && library[book] != state) {
		library[book] = state;
		return true;
	}
	return false;
}

/**
 * Report borrower message.
 * @param message the message to report
 */
void report(Borrower* borrower, const char message[]) {
	printf("Borrower %d [%2d]: %s\n", borrower->id, borrower->current_time, message);
}

/**
 * Borrow a book from the library.
 *
 * If the current time is before the library closing time,
 * the borrower uses a critical section to get a recommendation
 * from the library. If there is no recommendation, the borrower
 * reports "no book to borrow" for that time period.
 *
 * Otherwise, the borrower borrows the book, reports the loan as
 * "borrowed <book>", sets the due by time to the lesser of
 * the current time plus the library circulation period or the
 * library closing time, and increments the borrowed count for
 * the running total of books for the borrower.
 *
 * The recommended book is only guaranteed to be available if
 * borrowed in the same critical section. If the borrow operation
 * fails because the book is unavailable, the borrower reports
 * "***unavailable: <book>"
 */
void borrowBook(Borrower *borrower) {

	// check if library is open
	if (CLOSING_TIME <= borrower->current_time) {
		printf("Library is closed");
		return;
	}

	pthread_mutex_lock(&library_mutex);  //lock critical section

	// get book recommendation
	int book;
	book = recommendBook();
	// check if book is acutally a book
	if (book == NO_BOOK) {
		printf("Borrower %d: no book to borrow \n", borrower->id);
		//pthread_mutex_unlock(&library_mutex); // unlock critical section
	}
	else if (book != NO_BOOK) {
		// change book state
		if (setBookState(book, borrowed)) {
			// if book is valid, set as borrowers book
			borrower->book = book;
			// calculate lesser of two times and set return time
			int cTime = borrower->current_time;
			if ((cTime + CIRCULATION_PERIOD) < (cTime + CLOSING_TIME)) {
				borrower->due_by = cTime + CIRCULATION_PERIOD;
			} else {
				borrower->due_by = cTime + CLOSING_TIME;
			}
			// increment book count
			borrower->borrowed_count += 1;
		} else {
			//printf("Error setting book State \n");
			printf("***unavailable book: %d\n", book);
		}
	}
	pthread_mutex_unlock(&library_mutex); // unlock critical section
}

/**
 * Return borrower's book to the library.
 *
 * The borrower returns the book to the library within
 * a critical section, sets book to null, and reports
 * "returned <bookname>". If the return operation fails,
 * the borrower reports "***already returned <bookname>"
 */
void returnBook(Borrower *borrower) {


	pthread_mutex_lock(&library_mutex);  //lock critical section
	int book;
	book = borrower->book;
	// change book state
	if (setBookState(book, checked_in)) {
		printf("returned book: %d\n", book);
		// set borrowers book to null
		borrower->book = NO_BOOK;
		borrower->due_by = 0;
	} else {
		//printf("Error setting book State \n");
		printf("***already returned book: %d\n", book);
	}
	pthread_mutex_unlock(&library_mutex); // unlock critical section
}

/**
 * Run a borrower for an interval of time t borrow and
 * return library from a book collection.
 *
 * @param param arg pointer to the Borrower for this thread
 */
void *run(void *arg) {
	char msg[MAXBUF];
	Borrower *borrower = arg;

	// perform actions until library closes
	for ( ; borrower->current_time <= CLOSING_TIME; borrower->current_time++) {
		// delay so output displays more slowly
		sleep(1);

		if (borrower->book == NO_BOOK) {  // borrow one if has no book
			borrowBook(borrower);
		} else if (borrower->current_time >= borrower->due_by) { // book is due
			returnBook(borrower);
		} else {  // still have book
			sprintf(msg, "reading book %d", borrower->book);
			report(borrower, msg);
		}
	}
	sprintf(msg, "finished %d library", borrower->borrowed_count);
	report(borrower, msg);
	return NULL;
}

/**
 * Creates borrowers, and thread resources
 * for N_STUDENTS with N_MEAL_TICKETS.
 */
int main(void) {
	setlinebuf(stdout); // buffer lines
	printf("Start final-4\n");

	// initialize books in library
	for (int book = 0; book < N_BOOKS; book++) {
		library[book] = checked_in;
	}

	// array of borrowers
	Borrower borrowers[N_BORROWERS];

	// array of borrower threads
	pthread_t borrower_threads[N_BORROWERS];

	// create and run borrowers
	for (int id = 0; id < N_BORROWERS; id++) {
		// create borrower with id
		borrowers[id] = (Borrower){id, NO_BOOK, 0, 0, 0};

		// run borrower in thread
		pthread_create(&borrower_threads[id], NULL, run, &borrowers[id]);
	}

	// wait for borrowers
	for (int id = 0; id < N_BORROWERS; id++) {
		pthread_join(borrower_threads[id], NULL);
	}

	printf("End final-4\n");
}
