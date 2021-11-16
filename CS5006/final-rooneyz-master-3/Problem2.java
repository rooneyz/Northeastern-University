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
	 * To transform to a tail recursive function you must add an accumulator that will carry the current value as the
	 * recursive calls continue and then once the base case is reached return the accumulated value. Do the math going
	 * down instead of up (on the return).
	 * @param x
	 * @param n
	 * @param acc
	 * @return
	 */
	public static float power_tr(float x, int n, float acc) {
		assert n >= 0;

		if (acc == 0){acc = 1;}

		if (n == 0) {
			// base case
			return acc;
		} else if (n%2 == 1) {
			// transform to even exponent
			return  power_tr(x, n-1, x * acc);
		} else {
			// reduce by factor of 2 each time
			return power_tr(x * x, n/2,   acc);
		}
	}

	/**
	 * 2 parameter intermediate to call 3 parameter
	 * @param x
	 * @param n
	 * @return
	 */
	public static float power_tr(float x, int n) {
		float result = power_tr(x, n , 1);
		return result;
	}

	/**
	 * To convert from tail recursive to iterative first exchange base and tail recursive cases by inverting
	 * the base case condition. Remove recursive calls by looping once the base case is met it will drop out of the
	 * loop and return the acc value.
	 * @param x
	 * @param n
	 * @return
	 */
	public static float power_it(float x, int n) {
		assert n >= 0;

		// initialize acc
		float acc = 1;

		// loop and decrease n until the inverted base case is not true
		while (n != 0) {

			if (n%2 == 1) {
				// transform to even exponent
				acc *= x;
				n -= 1;

			} else {
				x *= x;
				n /= 2;
			}
		}
		return acc;
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
