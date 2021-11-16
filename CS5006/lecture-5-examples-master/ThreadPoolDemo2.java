/**
 * ThreadPoolDemo1.java
 */
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;  
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;  

/**
 * This class demonstrates the use of a basic Java
 * ThreadPool with Callable tasks that return values.
 * @author philip gust
 */
public class ThreadPoolDemo2 implements Callable<String> {
    /** The message to for this task */
	private String message;  
    
    /**
     * Create a new instance of the runnable
     * @param message the message to process.
     */
    public ThreadPoolDemo2(String message){  
        this.message = message;  
    }  
    
    /**
     * Perform the action for this task
     */
    public String call() {
    	String threadName = Thread.currentThread().getName();
        System.out.printf("%s (Start) message = %s\n", threadName, message);  
	    processMessage();  //processmessage sleeps the thread for 2 seconds  
	    System.out.printf("%s (End)\n", threadName); //prints thread name
	    return message;
	}
    
    /**
     * Process the message for this task.
     */
	private void processMessage() {  
	    try {  
	    	Thread.sleep(2000);  
	    } catch (InterruptedException e) { 
	    	e.printStackTrace(); 
	    }  
	}  

	/**
	 * Test thread pool for 5 threads and 10 tasks
	 * @param args unused
	 */
	public static void main(String[] args) {
		//create a fixed pool of 5 threads
	    ExecutorService executor = Executors.newFixedThreadPool(5);

	    // create a list of task results
	    List<Future<String>> results = new ArrayList<Future<String>>();
	    
	    // add ten tasks to the pool
	    for (int i = 0; i < 10; i++) {  
	        Callable<String> worker = new ThreadPoolDemo2(Integer.toString(i));  
	        // submit worker to pool
	        Future<String> future = executor.submit(worker);
	        results.add(future);  // save future results for display
	    }
	    
	    // shut down thread pool before exiting program
	    executor.shutdown(); 
	    
	    // give thread pool a chance to complete
	    boolean terminated = false;
	    try {
			terminated = executor.awaitTermination(1, TimeUnit.MINUTES);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	    if (!terminated) {
	    	List<Runnable> pendingTasks = executor.shutdownNow();
	    	System.out.printf("%d tasks not terminated.\n", pendingTasks.size());
	    } else {
	    	System.out.println("\nresults:");
	    	for (Future<String> future : results) {
	    		try {
					System.out.println(future.get());
				} catch (InterruptedException | ExecutionException e) {
					e.printStackTrace();
				}
	    	}
		    System.out.println("Finished all tasks");  
	    }	  
	}  
}