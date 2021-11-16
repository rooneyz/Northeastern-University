/*
 * FutureTaskExample.java
 */
import java.util.concurrent.*;

/**
 * This program demonstrates features of the FutureTask class,
 * how the task can be cancelled before it completes, and how
 * to check on whether the task has completed.
 * 
 * @author philip gust
 *
 */
public class FutureTaskCallableExample {
    public static void main(String[] args) throws InterruptedException, ExecutionException {
        long startTime = System.currentTimeMillis();

        Callable<String> callable = new Callable<String>() {
			@Override
			public String call()  {
				try {
					Thread.sleep(7000);
				} catch (InterruptedException e) {
					System.err.println("Interrupted");
					return "callable interrupted";
				}
				return "callable returned";
			}    	
        };
        
        FutureTask<String> myFutureTask = new FutureTask<>(callable);
        Thread taskThread = new Thread(myFutureTask, "future task");
        taskThread.start();
        
        while(!myFutureTask.isDone()) {
            System.out.println("Task is still not done...");
            Thread.sleep(1000);
            
            long elapsedTime = (System.currentTimeMillis() - startTime);
            if (elapsedTime > 5000) {	// change this value
                myFutureTask.cancel(true);
            }
        }

        if (myFutureTask.isCancelled()) {
        		System.out.println("Callable cancelled");
        		String result = myFutureTask.get();  // throws CancellationException
        		System.out.println(result);		// won't happen
        } else {
    			System.out.println("Callable not cancelled");
        		String result = myFutureTask.get();	// waits for callable to complete
        		System.out.println(result);
        }
    }
}
