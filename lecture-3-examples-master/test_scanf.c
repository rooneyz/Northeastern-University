/*
 * test_scanf.c
 * This program demonstrates using scanf
 * to read in numbers and strings. It can
 * read any other type as well.
 *
 *  Created on: May 21, 2019
 *      Author: phil
 */
#include <stdio.h>
#include <stdbool.h>

/**
 * Read a number from standard input
 *
 * @param numToRead reference to number read
 * @return true if successful
 */
bool readNumber(int *numToRead) {  // call by reference
	return (scanf("%d", numToRead) == 1);
}

/**
 * Read a number and string from standard input.
 * Input fields are separated by spaces, so scanf
 * stops reading the string at the first space.
 * Replace the "%s" format specifier with "%[^\n]"
 * to read up to but not including the end of line.
 *
 * @param numToRead reference to number read
 * @param strToRead string to read
 * @return number of read
 */
int readNumberAndString(int *numToRead, char strToRead[]) {  // call by reference
	return scanf("%d %s", numToRead, strToRead);
}

int main() {
	int value;
	char str[128];
	printf("enter a number: ");
	fflush(stdout);


	if (!readNumber(&value)) {
		fprintf(stderr, "not a number\n");
	} else {
		printf("read number: %d\n", value);
	}

	printf("enter a number and string: ");
	fflush(stdout);


	int nread = readNumberAndString(&value, str);
	if (nread != 2) {
		fprintf(stderr, "not a number and string: %d\n", nread);
	} else {
		printf("read number and string: %d %s\n", value, str);
	}
}

