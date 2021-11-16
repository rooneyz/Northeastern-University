/*
 * MonitorDemo.java
 *
 * This file illustrates the use of monitor to guard access to
 * a resource with threads in Java. When two threads share same
 * memory, use monitor to make it safe. Java uses scope to specify
 * a critical section locked by the monitor.
 *
 *  Created on: Apr 8, 2018
 *  Author: philip Gust
 */
public class MonitorDemo implements Runnable {  
	/** running used for both its value and its monitor. */
	static Boolean running[] = {true};
	
	/**
	 * This function is run by a thread.
	 */
    public void run() {
    	System.err.printf("    runner: beginning\n");
	    while(true) {
			try {
	    		// If main has monitor, thread waits; when main unlocks, thread continues
	    		System.err.printf("    runner: waiting for monitor on running\n");
	    		synchronized(running) {  // lock monitor within scope
	    			System.err.printf("    runner: locked monitor on running, value is %b\n", running[0]);
	    			if (!running[0]) break;
	    		}
			} finally {
				System.err.printf("    runner: unlocked monitor on running\n");
			}
    		while (true) {
    			try {
					Thread.sleep(1000);
					break;
				} catch (InterruptedException e) {
					// try again
				}
    		}
    	}
    	System.err.printf("    runner: finishing\n");
    }  

    /**
     * This function runs TestThreadMonitor thread, waits 5 seconds, 
     * then sets monitor value to false signaling the thread to terminate, 
     * then waits for thread to terminate
     */
    public static void main(String args[]) {
    	Thread thread = new Thread(new MonitorDemo(), "TestThreadMonitor");
    	synchronized(running) {
    		System.err.printf("main: locked monitor on running\n");
    		thread.start();
    		// runner thread started, but will wait for running monitor 
    		while(true) {
    			try {
    				Thread.sleep(2000);
    				break;
				} catch (InterruptedException e) {
					// try again
				} 
    		}
    		System.err.printf("main: unlocking monitor on running\n");
    	}
    	
    	// sleep to simulate work taking place
    	while(true) {
    		try {
    			Thread.sleep(5000);
    			break;
    		} catch (InterruptedException e) {
    			// try again
    		}
    	}
    	
    	// Lock the monitor, making it safe to alter 'running'
    	System.err.printf("main: waiting for monitor on running\n");
    	synchronized(running) { // lock monitor within scope
    		System.err.printf("main: locked monitor on running, setting false\n");
    		running[0] = false;
    	}
		System.err.printf("main: unlocked monitor on running\n");

    	try {
			thread.join();
		} catch (InterruptedException e) {
			System.err.printf("main: join failed");
		}
	    System.err.printf("main: finished");
    }
}  