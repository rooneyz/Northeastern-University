// Student: Zach Rooney
// 2019-08-03

import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveAction;


/**
 * This class is a simplified version of java.util.parallelSort().
 *
 * @author philip gust
 */
@SuppressWarnings("serial")
public class ParrallelQuickSort extends RecursiveAction {


    /**
     * value array, and indexes to interval [left …right) in the array.
     */
    int values[], left, right;

    /**
     * Construct parallel sorter for values array from
     * [left, right) using scratch array as temporary storage
     *
     * @param values the array to sort
     * @param left   index of first element to sort
     * @param right  index beyond last value to sort
     */
    ParrallelQuickSort(int[] values, int left, int right) {
        this.values = values;
        this.left = left;
        this.right = right;
    }

    /**
     * partition will partition the array with a pivot and sort higher values to its right and
     * lower values to the left. Returns the index to the right of the pivot
     */
    int partition(int values[], int left, int right) {
        // get needed values
        int pivot = right;
        int smaller = left - 1;

        for (int l = left; l <= right - 1; l++) {
            if (values[l] <= values[pivot]) {
                smaller++;

                // swap
                int temp = values[smaller];
                values[smaller] = values[l];
                values[l] = temp;
            }
        }

        int temp = values[smaller + 1];
        values[smaller + 1] = values[pivot];
        values[right] = temp;

        return smaller + 1;

    }

    /**
     * Divide input array in half, and invoke sort them as concurrent
     * sub-tasks.
     *
     * @see java.util.concurrent.RecursiveTask#compute()
     */
    @Override
    protected void compute() {

        if ((left >= right)
                || (ForkJoinPool.getCommonPoolParallelism() == 1)) {
            System.out.printf("%s: %d %d\n", Thread.currentThread().getName(), left, right);
        } else {
            int part = partition(values, left, right);
            System.out.printf("%s: %d %d %d\n", Thread.currentThread().getName(), left, part, right);

            // run sub=tasks, automatically forking for one of the two,
            // and wait for completion of both sub-tasks
            invokeAll(new ParrallelQuickSort(values, left, part - 1),
                    new ParrallelQuickSort(values, part + 1, right));
        }
    }


    /**
     * Parallel sort an array
     *
     * @param values
     */
    static public void sort(int[] values) {
        ForkJoinPool.commonPool().invoke(
                new ParrallelQuickSort(values, 0, values.length - 1));
    }

    /**
     * Sort sample array using parallel sorter.
     *
     * @param args
     */
    public static void main(String[] args) {
        int values[] = {0, 2, 10, 5, -6, 7, 20, 2};
        ParrallelQuickSort.sort(values);
        for (int val : values) {
            System.out.printf("%d ", val);
        }
        System.out.println();
    }
}

