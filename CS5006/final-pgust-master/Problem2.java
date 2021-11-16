/*
 * Problem2.java
 *
 * CS 5006 Final Exam
 * Problem 1
 *
 * The function power_nt() below, which is not tail-recursive,
 * computes single-precision X raised to the unsigned int power N.
 *
 * This problem is to:
 *
 * 1) create an equivalent function power_tr that transforms
 * power_nt() to be strictly tail recursive using the technique
 * shown in the module 2 lecture and class notes
 *
 * 2) create an equivalent function power_it that transforms
 * power_tr() to be iterative using the technique shown in the
 * module 2 lecture and class notes.
 *
 * Note: this problem will be graded entirely on the application
 * of the techniques shown in the module2 lecture and class notes.
 * In other words, this problem is all about the techniques. Work
 * it out yourself: a function from the web will not serve the
 * purpose.
 *
 * Include a description in the function headers of how you used
 * the techniques to transform the non tail-recursive to the tail-
 * recursive form and the tail-recursive to the iterative form.
 * Also use internal comments to provide specific details.
 *
 * Do not clean up the code as it will obscure how you applied
 * the techniques.
 */

final public class Problem2 {
	/**
	 * Computes X raised to power N. This function is 
	 * not tail recursive.
	 *
	 * @param x the base
	 * @param n a non-negative exponent
	 * @return x raised to the power n
	 */
	public static float power_nt(float x, int n) {
		assert n >= 0;
		
		if (n == 0) {
			// base case
			return 1;
		} else if (n%2 == 1) {
			// transform to even exponent
			return x * power_nt(x, n-1);
		} else {
			// reduce by factor of 2 each time
			return power_nt(x*x, n/2);
		}
	}

	/**
	 * Computes X raised to the power N. Transforms the
	 * non tail-recursive form into tail recursive with the
	 * addition of an parameter that accumulates results.
	 *
	 * @param x the base
	 * @param n a non-negative exponent
	 * @param acc the accumulated result
	 * @return x raised to the power n
	 */
	private static float power_tr_ac(float x, int n, float acc) {
		if (n == 0) {
			// base case: return accumulated result
			return acc;
		} else if (n%2 == 1) {
			// transform to use of even exponent
			return power_tr_ac(x, n-1, acc*x);
		} else {
			// reduce by factor of 2 each time
			return power_tr_ac(x*x, n/2, acc);
		}
	}

	/**
	 * Computes X raised to the power N. Calls tail-recursive
	 * support function with addition of an parameter that 
	 * accumulates results.
	 *
	 * @param x the base
	 * @param n a non-negative exponent
	 * @param acc the accumulated result
	 * @return x raised to the power n
	 */
	public static float power_tr(float x, int n) {
		assert n >= 0;
		
		return power_tr_ac(x, n, 1);
	}

	/**
	 * Computes X raised to the power N. Transforms the
	 * tail-recursive functions into iteration by converting
	 * negated condition to while loop on inductive case, 
	 * and returning base case value as the function result
	 * at end of loop.
	 *
	 * @param x the base
	 * @param n a non-negative exponent
	 * @return x raised to the power n
	 */
	public static float power_it(float x, int n) {
		assert n >= 0;

		float acc = 1;
		while (n != 0) { // negate original base condition
			if (n%2 == 1) {
				// transform to use of even exponent
				acc = acc*x;
				n = n-1;
			} else {
				// reduce by factor of 2 each time
				x = x*x;
				n = n/2;
			}
		}
		return acc;  // original base case value
	}

	/**
	 * Exercise the three versions of the power function.
	 * @param args unused
	 */
	public static void main(String[] args) {
		System.out.printf("CS 5006 Problem 2\n");
		float x = -5.5f;
		float nt=0f, tr=0f, it=0f;
		for (int n = 0; n < 5; n++) {
			nt = power_nt(x,n);  // non tail-recursive
			tr = power_tr(x,n);  // tail recursive
			it = power_it(x,n);  // iterative

			System.out.printf("power(%f,%d): nt=%f tr=%f it=%f\n", x, n, nt, tr, it);
		}
	}

}
