/**
 * Problem4.java
 *
 * Problem 4
 * CS 5006 Final Exam
 * 
 * Given an even power-of-2 sized array: 
 *   [ a1, a2, a3, a4, ……, an, b1, b2, b3, b4, …., bn ]
 * 
 * shuffle the lower and upper sub-arrays without using 
 * extra space. 
 *   [ a1, b1, a2, b2, a3, b3, ……, an, bn ]
 * 
 * This is a divide and conquer problem. Logically divide 
 * the array in half and swap the second half elements of
 * the lower sub-array with first half elements of upper 
 * sub-array. Then apply this algorithm recursively to the 
 * lower and upper sub-arrays.
 *
 * Here is an example with an 8-element array.
 *   [ a1, a2, a3, a4, b1, b2, b3, b4 ]
 *   
 * Logically divide the array into two sub-arrays: 
 *   [ a1, a2, a3, a4 : b1, b2, b3, b4 ]
 *
 * Exchange top-half elements of lower array with bottom-
 * half element of upper array: 
 *   [ a1, a2, b1, b2 : a3, a4, b3, b4 ]
 *             '----'   '----'
 *             
 * Recursively divide the lower sub-array [ a1, a2, b1, b2 ] 
 * into sub-arrays:
 *   [ a1, a2 :  b1, b2 ]
 *   
 * Again, exchange top-half elements of lower array with
 * bottom-half elements of upper array:
 *   [ a1, b1 :  a2, b2 ]
 *         --    --
 *         
 * The lower sub-array [ a1, b1 ] is size 2, so it is 
 * already merged.
 * 
 * Repeat the same steps for the upper sub-arrays.    
 */

import java.util.Arrays;

public final class Problem4 {
	/**
	 * Shuffle together the lower and upper halves of
	 * the array using no additional storage. The number 
	 * of elements must be an even power of 2.
	 * 
	 * @param a the array
	 * @param first the index of the first element
	 * @param last the index of the last element
	 */
    public static void shuffleArray(int a[], int first, int last) {
        // If only 2 element, return
        if (last - first == 1) {
            return;
        }
        
        // upper is index of bottom half of upper sub-array
        int upper = 1 + (first+last)/2;
        
        // lower is index of top half of lower sub-array
        int lower = (first+upper)/2;
      
        // Swap elements of top half of lower sub-array
        // and bottom half of upper sub-array
        for (int l = lower, u = upper; l < upper; l++, u++) {
            int tmp = a[l];
            a[l] = a[u];
            a[u] = tmp;
        }
      
        // Recursively doing for first half and second half
        shuffleArray(a, first, upper-1);
        shuffleArray(a, upper, last);
    }
     
    /**
     * Test function for the array
     * 
     * @param args unused
     */
    public static void main(String[] args)
    {
        System.out.println("Start problem 4\n");

        // a: size 2
        int a[] = { 1, 2 };
        System.out.println("\na) original:");
        System.out.println(Arrays.toString(a));
      
        shuffleArray(a, 0, a.length - 1);
        System.out.println("\na) actual:");
        System.out.println(Arrays.toString(a));
        
        System.out.println("\na) expected:");
        System.out.println("[1, 2]");
        
        // b: size 4
        int b[] = { 1, 3, 2, 4 };
        System.out.println("\nb) original:");
        System.out.println(Arrays.toString(b));
      
        shuffleArray(b, 0, b.length - 1);
        System.out.println("\nb) actual:");
        System.out.println(Arrays.toString(b));
        
        System.out.println("\nb) expected:");
        System.out.println("[1, 2, 3, 4]");
        
        // c: size 8
        int c[] = { 1, 3, 5, 7, 2, 4, 6, 8 };
        System.out.println("\nc) original:");
        System.out.println(Arrays.toString(c));
      
        shuffleArray(c, 0, c.length - 1);
        System.out.println("\nc) actual:");
        System.out.println(Arrays.toString(c));
        
        System.out.println("\nc) expected:");
        System.out.println("[1, 2, 3, 4, 5, 6, 7, 8]");
        
        System.out.println("\nEnd problem 4");
    }
}
