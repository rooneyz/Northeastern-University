/**
 * ParallelSortDemo.java 
 */

import java.util.Arrays;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveAction;

/**
 * This class is a simplified version of java.util.parallelSort().
 * 
 * @author philip gust
 */
@SuppressWarnings("serial")
public class ParallelSortDemo extends RecursiveAction {
    /**
     * The minimum array length below which a parallel sorting
     * algorithm will not further partition the sorting task.
     */
    private static final int MIN_ARRAY_SORT_GRAN = 2;

	/** value array, and indexes to interval [left …right) in the array. */
    int values[], left, right;
    
    /**
     * Construct parallel sorter for values array from 
     * [left, right) using scratch array as temporary storage
     * @param values the array to sort
     * @param left index of first element to sort
     * @param right index beyond last value to sort
     */
	ParallelSortDemo(int[] values, int left, int right) {
		this.values = values;
		this.left = left;
		this.right = right;
	}

	/**
	 * Merge presorted sub-arrays left [left..mid) and
	 * right [mid..right), using scratch for temp storage.
	 */
	void merge() {
		// merge arrays using scratch temporary storage;  
		// l and r are to the positions in left and right sub-arrays
		int mid = (left+right)/2;
		int len = right-left;
		int[] scratch = new int[len];
		
		for (int l = left, r = mid, i = 0; i < len; i++)  {
			if (l < mid  && (r == right || values[l] < values[r])) {
				scratch[i] = values[l++];
			} else {
				scratch[i] = values[r++];
			}
		}

		// copy sorted sub-array back to the input
		for (int i = left; i < right; i++) {
			values[i] = scratch[i-left];
		}
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
		int len = right-left;
		if (    (len <= MIN_ARRAY_SORT_GRAN) 
        	||  (ForkJoinPool.getCommonPoolParallelism() == 1)) {
        	System.out.printf("%s: %d %d\n",Thread.currentThread().getName(), left, right);
            Arrays.sort(values, left, right);
		} else {
    		int mid = (left+right)/2;
    		System.out.printf("%s: %d %d %d\n",Thread.currentThread().getName(), left, mid, right);
    		
    		// run sub=tasks, automatically forking for one of the two,
    		// and wait for completion of both sub-tasks
    	    invokeAll(new ParallelSortDemo(values, left, mid),
    	    		  new ParallelSortDemo(values, mid, right));
    	    
    		// merge presorted subranges
    		merge();
    	}
	}

	/**
	 * Parallel sort an array
	 * @param values
	 */
	static public void sort(int[] values) {
		ForkJoinPool.commonPool().invoke(
			new ParallelSortDemo(values, 0, values.length));		
	}
	/**
	 * Sort sample array using parallel sorter.
	 * @param args
	 */
	public static void main(String[] args) {
		int values[] = {0, 2, 10, 5, -6, 7, 20, 2};
		ParallelSortDemo.sort(values);
		for (int val : values) {
			System.out.printf("%d ", val);
		}
		System.out.println();
	}
}
