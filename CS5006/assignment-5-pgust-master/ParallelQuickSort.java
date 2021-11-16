/**
 * ParallelSort.java 
 */

import java.util.Arrays;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveAction;

/**
 * This class implements a parallel QuickSort algorithm
 * similar to java.util.parallelSort().
 * 
 * @author philip gust
 */
@SuppressWarnings("serial")
final public class ParallelQuickSort extends RecursiveAction {
    /**
     * The minimum array length below which a parallel sorting
     * algorithm will not further partition the sorting task.
     */
    private static final int MIN_ARRAY_SORT_GRAN = 2;
    private final boolean debug = false;

    private int values[];   // array to sort
    private final int lo;   // low index in array
    private final int hi;   // high index in array
	
    /**
     * Constructor for parallel quicksort class.
     * @param values // array to sort
     * @param lo  // low index in array
     * @param hi  // high index in array
     */
	ParallelQuickSort(int[] values, int lo, int hi) {
		this.values = values;
		this.lo = lo;
		this.hi = hi;
	}

	/**
	 * Swap array values in-place.
	 *
	 * @param i the first index
	 * @param j the second index
	 */
	private void swap (int i, int j) {
		int t = values[i];
		values[i] = values[j];
		values[j] = t;
	}
	
	/**
	 * Partition array between lo and hi, and return the pivot point index.
	 *
	 * @return the pivot point index
	 */
	private int partition () {
		int pv = hi;    	// pivot about hi value
		int i = lo-1;       // index of smaller element
		for (int j = lo; j <= hi-1;  j++) {
			if (values[j] <= values[pv]) {
				swap(++i, j);  // increment index of smaller element
			}
		}
		swap(++i, pv); // increment index of smaller element
		return i;
	}
	
	/**      
	 * Divide input array in half, and invoke sort them as concurrent 
	 * sub-tasks. If size of input is below threshold or only one thread 
	 * available, use standard sort.
     *
	 * @see java.util.concurrent.RecursiveTask#compute()
	 */
	@Override
	protected void compute() {
		int length = hi-lo+1;
		if (length <= 1) {
			// already sorted
        	if (debug) System.out.printf("%s: %d\n",Thread.currentThread().getName(), lo);
		} else if (    (length <= MIN_ARRAY_SORT_GRAN) 
				   ||  (ForkJoinPool.getCommonPoolParallelism() == 1)) {
        	if (debug) System.out.printf("%s: %d %d\n",Thread.currentThread().getName(), lo, hi);
            Arrays.sort(values, lo, hi+1);
		} else {
			// partition a so a[i] <= a[p] <= a[j], ( lo <= i < p < j <= hi)
			int p = partition();  // partition a[lo..hi]
    		if (debug) System.out.printf("%s: %d %d %d\n",Thread.currentThread().getName(), lo, p, hi);
    		
    		// run sub=tasks, automatically forking for one of the two,
    		// and wait for completion of both sub-tasks
    	    invokeAll(new ParallelQuickSort(values, lo, p-1),
    	    		  new ParallelQuickSort(values, p+1, hi));
    	}
	}

	/**
	 * Parallel sort an array.
	 * @param values the values to sort
	 */
	static public void sort(int[] values) {
		ForkJoinPool.commonPool().invoke(
			new ParallelQuickSort(values, 0, values.length-1));		
	}
	
	/**
	 * Tests ParallelQuickSort class.
	 * @param args unused
	 */
	public static void main(String[] args) {
		int values[] = {0, 2, 10, 5, -6, 7, 20, 2};
		ParallelQuickSort.sort(values);
		
		// print the array
		for (int val : values) {
			System.out.print(val);
			System.out.print(" ");
		}
		System.out.println();
	}
}
