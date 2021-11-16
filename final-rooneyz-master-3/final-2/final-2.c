/*
 * problem2.c
 *
 * This problem is to write the supporting functions that
 * enable a version of Insertion Sort to sort the integer
 * values in a random-access binary integer file.
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * Get the value at the index position in the array file.
 * @param f the array file
 * @param index the index position
 * @return the value at the position
 */
int getValueAt(FILE* f, size_t index) {

		fseek(f, (index*sizeof(int)), SEEK_SET);
		int temp;
		if (fread(&temp, sizeof(int), 1, f) < 1) {
			printf("Error reading array\n");
			fclose(f);
			return EXIT_FAILURE;
		}
		rewind(f);

		printf("%d", temp);
		return temp;
}

/**
 * Set the value at the index position in the array file.
 * @param f the array file
 * @param index the index position
 * @param the value to set
 */
void setValueAt(FILE* f, size_t index, int value) {

		// update value at given position
		fseek(f, (index*sizeof(int)), SEEK_SET); // position before index
		int newval = value; // set new value to value given
		if (fwrite(&newval, sizeof(int), 1, f) < 1) {	// Replace value
			printf("Error writing array\n");
			fclose(f);
			exit;
		}

		rewind(f);  // move back to start of tmpf

}

/**
 * Get the number of elements in the array file.
 * @param f the array file
 * @return the number of elements
 */
size_t getArraySize(FILE* f) {

	fseek(f, 0, SEEK_END); // seek to end of file
	size_t size = ftell(f); // get current file pointer
	size = size / sizeof(int);
	//printf("%d", size);  // For Debug
	rewind(f);   // reset pointer

	return size;
}

/**
 * Write the input array to the file.
 * @param f the array file
 * @param the array values
 * @param the array size
 */
void writeArray(FILE* f, int values[], size_t size) {
	fseek(f, 0, SEEK_SET);  // beginning of file
	fwrite(values, sizeof(int), size, f);
}

/**
 * Print the array.
 * @param f the array file
 */
void printArray(FILE* f) {
	fseek(f, 0, SEEK_SET); // beginning of file
	int val;
	// iterate for all values in the array file
	for (int i = 0; fread(&val, sizeof(int), 1, f) == 1; i++) {
		printf("%d: %d\n", i, val);
	}
}

/**
 * Insertion Sort inserts each element of the array into
 * its proper position, leaving progressively larger
 * stretches of the array sorted.
 *
 * @param f file the array file
 */
void insertionSort(FILE* f) {
	size_t nValues = getArraySize(f);
	for (int i=1; i < nValues; i++) {
		// slide values up array to make "hole" for value
		int hole = i;
		int val = getValueAt(f, hole);
		int preval;  // value at hole-1
		while(hole > 0 && (preval = getValueAt(f, hole-1)) > val) {
			setValueAt(f, hole, preval);
			hole--;
		}
		// put value in "hole" position
		setValueAt(f, hole, val);
	}
}

#if defined __MINGW32__
#include <string.h>
// mingw tmpfile() creates files in "C:\" => no permission
FILE *tmpfile() {
	char tmppath[FILENAME_MAX];
	sprintf(tmppath,"%s\\final-2.tmp",getenv("TEMP"));
	return fopen(tmppath, "w+b");
}
#endif

/**
 * This program sorts an array of integers using
 * a file-based version of insertion sort.
 */
int main(void) {
	printf("Start final-2\n");

	// array to sort
	int a[] = {4, 3, 1, 5, 2};

	// write array to a binary temp file that is
	// automatically removed when it is closed
	FILE* f = tmpfile();

	if (f == NULL) {
		perror("cannot open temp file");
		fflush(stdout);
		fflush(stderr);
		exit(EXIT_FAILURE);
	}
	writeArray(f, a, 5);

	// print unsorted array
	printf("unsorted:\n");
	printArray(f);

	// sort the array
	insertionSort(f);

	// print sorted array
	printf("\nsorted:\n");
	printArray(f);

	// close the temp file
	fclose(f);

	printf("End final-2\n");
}
