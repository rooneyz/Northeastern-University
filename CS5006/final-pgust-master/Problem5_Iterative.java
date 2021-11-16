/*
 * Problem5_Iterative.java
 * 
 * Problem 5
 * CS 5006 Final Exam
 *
 * Every positive rational number can be represented as whole 
 * number plus a sum of fractions whose numerator is 1 and 
 * whose denominator is a positive whole number, such as 1/3.
 *
 * Following are few examples:
 * 7/5 = 1 + 1/3 + 1/15
 * 2/3 = 1/2 + 1/6
 * 6/14 = 1/3 + 1/11 + 1/231
 * 12/13 = 1/2 + 1/3 + 1/12 + 1/156
 *
 * These fractions can be generated by a Greedy Algorithm based on
 * reduce and conquer. For a positive numerator num and a positive 
 * denominator den, if num >= den, then print the whole portion 
 * and recur for the fraction. For num < den, print the greatest 
 * fraction whose numerator is 1, then recur for the remainder.
 * 
 * For 7/5, the numerator is greater than the denominator so we
 * output the whole portion of 7/5 = 1, and recur for the remainder 
 * (7 - (1*5))/5 = 2/5. 
 * 
 * The ceiling of the reciprocal fraction 5/2 is 3, so we output 1/3, 
 * and recur for the remainder (2/5 - 1/3) = ((2*3) - (5*1)) / (3*5) 
 * = 1/15. 
 * 
 * The ceiling of the reciprocal fraction 15/1 is 15, so we output 
 * 1/15 and recur for the remainder (1/15 - 1/15) = 0/15.
 * 
 * Since the numerator is 0, the algorithm is done.
 */
public class Problem5_Iterative {
	/**
	 * This function prints a series of fractions for numerator num
	 * and denominator den whose numerator is 1 and whose denominator 
	 * is a positive whole number.
	 *
	 * @param num non-negative numerator
	 * @param den positive denominator
	 */
	static public void printFractions(int num, int den) {
		// print whole part if nr >= dr
		int n = num/den;
		String sep = "";
		if ((n > 0) || (num == 0)) {
		    System.out.printf("%d",  n); // print whole part
		    
		    // recur for remainder
		    num = num - n*den;
		    sep = " + ";
		}
		
		// print fractions for remainder
		while (num > 0) {
			System.out.print(sep); // separator from previous term
			
			n = (den-1)/num + 1;  // ceiling or reciprocal fraction
			System.out.printf("1/%d", n); // print fraction

			// recur for remainder
			num = num*n - den;
			den *= n;
			sep = " + ";
		}
	}
	 
	/**
	 * Main program tests the function for a variety of inputs
	 * @param args unused
	 */
	public static void main(String args[]) {
		System.out.println("Start problem 5\n");
		
		int[] numerator =   { 0, 8, 4, 2,  6, 12, 7 };
		int[] denominator = { 3, 4, 8, 3, 14, 13, 5 };
		String[] expected = {
				"0",
				"2",
				"1/2",
                "1/2 + 1/6",
		        "1/3 + 1/11 + 1/231",
		        "1/2 + 1/3 + 1/12 + 1/156",
		        "1 + 1/3 + 1/15"
		};
		
		for (int i = 0; i < expected.length; i++) {
		        int nr = numerator[i], dr = denominator[i];
		        System.out.printf("Representation of %d/%d is:\n", nr, dr);
		        printFractions(nr, dr);
		        System.out.printf("\nExpected:\n%s\n\n", expected[i]);
		}
		
		System.out.println("End problem 5");
	}
}
