/*
 * quicksort_stack.cpp
 *
 *  @since 2018-03-09
 *  @uthor philip gust
 */

#include <stdio.h>
#include <stdlib.h>


/**
 * Swap array values in-place.
 *
 * @param a the array
 * @param i the first index
 * @param j the second index
 */
void swap (int a[], int i, int j) {
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
}

/**
 * Partition to array and return the pivot point index.
 *
 * @param a the array
 * @param lo the low index
 * @param hi the high index
 * @return the pivot point index
 */
int partition (int a[], int lo, int hi) {
    int pv = hi;    	// pivot about hi value
    int i = lo-1;       // index of smaller element
    for (int j = lo; j <= hi-1;  j++) {
		if (a[j] <= a[pv]) {
			swap(a, ++i, j);  // increment index of smaller element
        }
    }
    swap(a, ++i, pv); // increment index of smaller element
    return i;
}

/**
 * Sort the input array between the low and high index.
 *
 * @param a the array
 * @param lo the low index
 * @param hi the high index
 */
void quicksort(int a[], int lo, int hi) {
	int stk[2*(hi-lo+1)];	// stack array
	int stksp = 0;			// stack pointer

	stk[stksp++] = lo;  // push lo
	stk[stksp++] = hi;  // push hi

	while (stksp > 0) {
		// get next pair of low/high indices
		hi = stk[--stksp]; // pop hi
		lo = stk[--stksp]; // pop lo

		// set pivot element to correct position
		int p = partition(a, lo, hi);

		// if elements to left of pivot, push to stack
		if (p-1 > lo) {
			stk[stksp++] = lo;  // push lo
			stk[stksp++] = p-1;	// push p-1
		}

		// if elements to right of pivot, push to stack
		if (p+1 < hi) {
			stk[stksp++] = p+1;	// push p+1
			stk[stksp++] = hi;	// push hi
		}
	}
}

/**
 * Print usage message.
 */
void usage() {
	fprintf(stderr, "usage: quicksort [n1 ... nk]\n");

}

/**
 * Print the array.
 *
 * @param a the array
 * @param size the array size
 */
void printArray(int a[], int size) {
	const char *sep = "";
	for (int i = 0; i <  size; i++) {
		printf("%s%d", sep, a[i]);
		sep = " ";
	}
	printf("\n");
}

/**
 * Test quicksort function. Arguments are the input
 * numbers and the output is the sorted numbers.
 *
 * @param argc the number of arguments
 * @param argv the arguments
 * @return status EXIT_SUCCESS for success, EXIT_FAILURE
 *   if input is invalid
 */
int main(int argc, char *argv[]) {
	if (argc > 1) {
		// get array from input arguments
		int a[argc-1];
		for (int i = 1; i < argc; i++) {
			if (sscanf(argv[i], "%d", &a[i-1]) != 1) {
				usage();
				return EXIT_FAILURE;
			}
		}

		// print input array
		printf("input array:  ");
		printArray(a, argc-1);

		// sort the array
		quicksort(a, 0, argc-2);

		// print sorted array
		printf("sorted array: ");
		printArray(a, argc-1);
	}
	return EXIT_SUCCESS;
}

