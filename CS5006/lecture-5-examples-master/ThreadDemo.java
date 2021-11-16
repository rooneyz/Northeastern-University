/**
/*
 * ThreadDemo.java
 *
 * This file illustrates the use of Java threads.
 * 
 * @date July 29, 2019
 * @author philip gust
 */

final public class ThreadDemo {
	
	/**
	 * This class computes the sum of the first N natural numbers
	 */
	static final public class SumOfN implements Runnable {
		private int sum = -1;
		final private int upper;
		
		/**
		 * Initialize class to compute sum of first N natural numbers.
		 * @param upper the upper value
		 */
		public SumOfN(int upper) {
			this.upper = upper;
		}
		
		/**
		 * Run thread to compute sum of first <upper> integers
		 */
		@Override
		public void run() {
			sum = 0;  // initialize global

			for (int i = 1; i <= upper; i++) {
				sum += i;
			}
			String threadName = Thread.currentThread().getName();
			System.out.printf("run() [thread %s]: sum is %d\n", threadName, sum);
		}
		
		/**
		 * Get sum after running this instance.
		 * @return the sum of first <upper> integers
		 */
		public int getSum() {
			return sum;
		}
		
	}

	/**
	 * This function reads a non-negative value parameter
	 * and runs a thread that sets global sum to the sum of
	 * numbers between 1 and that value.
	 */
	public static void main(String[] args) {
		if (args.length != 1) {
			System.err.printf("usage: ThreadDemo max_value\n");
			System.exit(1);
		}
		int maxval = 0;
		try {
			maxval = Integer.parseInt(args[0]);
			if (maxval < 0) {
				System.err.printf("Input value cannot be negative\n");
				System.exit(1);
			}
		} catch (NumberFormatException e) {
			System.err.printf("Input value must be non-negative number\n");
			System.exit(1);
		}

		// initialize thread attributes
		System.out.printf("main(): running thread to compute sum from 1 to %d\n", maxval);
		SumOfN sumofn = new SumOfN(maxval);
		Thread t = new Thread(sumofn, "TestThread");
		String tname = t.getName(); 
		
		// start thread
		t.start();
		System.out.printf("main(): created thread %s: waiting for it to exit\n", tname);

		// wait for thread to exit
		try {
			t.join();
		} catch (InterruptedException e) {
			System.err.printf("Join interrupted\n");
			System.exit(1);
		}

		// report sum
		System.out.printf("main(): thread %s exited normally\n", tname);
		System.out.printf("main(): thread %s returned sum = %d\n", tname, sumofn.getSum());
	}

}
