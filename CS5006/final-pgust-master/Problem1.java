/**
 * Problem1.java
 * 
 * This file illustrates an algorithm for counting duplicate
 * values in an array of integers. Problem 1 is to analyze
 * the algorithm.
 */
final public class Problem1 {
	/**
	 * Counts number of array elements that are duplicates
	 * of at least one other element in the array.
	 *
	 * @param size the array size
	 * @param a the array
	 * @param number of duplicate elements
	 */
	public static int countDuplicates(int[] a) {
		int count = 0;
		for (int i = 0; i < a.length; i++) {
			// find duplicate value for a[i] after it
			for (int j = i+1; j < a.length; j++) {
	    		if (a[i] == a[j]) { // count duplicate
	    			count++;
					break;
				}
			}
		}
		return count;
	}

	public static void main(String[] args) {
		int[] a = {1, 10, 20, 1, 25, 1, 10, 30, 25, 1};
		int dupCount = countDuplicates(a);
		System.out.printf("Total number of duplicate elements = %d\n", dupCount);
	}
}
