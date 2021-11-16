// Author: Phil Gust, Modified by: Zach Rooney
// Date: 2019-07-26

/**
 * Investment.java
 * 
 * This program selects an optimal investment portfolio
 * using a greedy algorithm that prioritizes the most
 * shares of the highest yielding bond first.
 * 
 */
import java.util.*;

import org.junit.FixMethodOrder;
import org.junit.Test;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;
import org.junit.runners.MethodSorters;

import static org.junit.Assert.assertEquals;

/**
 * This is a wrapper class for the Bond and 
 * HighestBondYieldComparator, and the unit
 * test class TestInvestment.
 */
public class Investment {	
	/**
	 * This class represents a Bond.	 *
	 */
	static public final class Bond  {
		// instance variables
		public String name;
		public double shares;
		public double cost;
		public double yield;

		/**
		 * Constructor
		 * @param name
		 * @param shares
		 * @param cost
		 * @param yield
		 */
		public Bond(String name, double shares, double cost, double yield) {
			this.name = name;
			this.shares = shares;
			this.cost = cost;
			this.yield = yield;
		}

		/**
		 * Default constructor
		 */
		public Bond() {
			this.name = "none";
			this.cost = 0;
			this.shares = 0;
			this.yield = 0;
		}

		/**
		 * Returns the total cost of the bond offering
		 * @return
		 */
		public double totalCost(){
			return (shares * cost);
		}

		/**
		 * Returns the total profit of the bond offering
		 * @return
		 */
		public double totalProfit(){
			return (totalCost() * yield);
		}



		/**
		 * Returns string representation of the bond object
		 * @return
		 */
		@Override
		public String toString() {
			return "Bond{" +
					"name='" + name + '\'' +
					", shares=" + shares +
					", cost=" + cost +
					", yield=" + yield +
					'}';
		}
	}
	
	/**
	 * This class orders bonds from highest to lowest yield.
	 */
	static class HighestBondYieldComparator implements Comparator<Bond> {
		public int compare(Bond bond1, Bond bond2) {

			if (bond1 == null && bond2 == null){
				return 0;
			}
			else if (bond2 == null){
				return -1;
			}
			else if (bond1 == null){
				return 1;
			}
			else if (bond1.yield > bond2.yield){
				return -1;
			}
			else if (bond1.yield < bond2.yield){
				return 1;
			}
			else {return 0;}
		}
	}

	/**
	 * Returns the optimum list of bonds from a bond priority queue.
	 * @param total total amount available to invest
	 * @param bonds collection of investment opportunities
	 * @return a portfolio of bonds
	 */
	static Collection<Bond> invest(float total, Collection<Bond> bonds) {
		// heap size
        final int heapSize = bonds.size();
        // amount of money
        double money = total;

	    ArrayList<Bond> portfolio = new ArrayList<>();
		PriorityQueue<Bond> catalog = new
                PriorityQueue<>( heapSize, new HighestBondYieldComparator());

		// add bonds to catalog
		for (Bond b : bonds){
			catalog.add(b);
		}

		// For Debug
//		for (Bond e : catalog){
//            System.out.println(e);
//        }
//        System.out.println("******************");

		// buy best bonds
		for (Bond e : catalog){
			//System.out.println(money);  // for Debug
			if (money > 0){
				if (money >= e.totalCost()){
					money -= e.totalCost();
					portfolio.add(e);
				}
				else if (money < e.totalCost()){
					double fraction = (money / (e.cost));
					money -= fraction;
					Bond temp = new Bond(e.name, fraction, e.cost, e.yield);
					portfolio.add(temp);
				}
			}

		}
		Collection<Bond> result = portfolio;

		// For Debug
//		for (Bond e : result){
//			System.out.println(e);
//		}
//		System.out.println("**************************");

		return result;
	}
	
	/**
	 * Unit test class for investments.
	 */
	@FixMethodOrder(MethodSorters.NAME_ASCENDING)
	static public class TestInvestment {
		/**
		 * Total the bonds in a portfolio.
		 * @param bonds the collection of bonds
		 * @return to total cost of the bonds
		 */
		float totalCost(Collection<Bond> bonds) {
			float total = 0;
			for (Bond bond : bonds) {
				total += bond.totalCost();
			}
			return total;
		}
		
		/**
		 * Total profit of the bonds in a portfolio.
		 * @param bonds the collection of bonds
		 * @return to total profit of the bonds
		 */
		float totalProfit(Collection< Bond> bonds) {
			float total = 0;
			for (Bond bond : bonds) {
				total += bond.totalProfit();
			}
			return total;
		}
		/**
		 * Test purchasing all bonds with funds left over.
		 */
		@Test
		public void test_0010_tooMuchToInvest() {
			Bond[] bonds = {
			    new Bond("ACME", 50f, 10f, 0.060f),	
			    new Bond("MERC", 20f, 20f, 0.095f),	
			    new Bond("COKE", 100f, 30f, 0.020f)
			};
			Collection<Bond> investments = invest(4000f, Arrays.asList(bonds));
			
			assertEquals(3, investments.size());
			assertEquals(3900, totalCost(investments), 0f);
			assertEquals(128f, totalProfit(investments), 0.001f);
		}

		/**
		 * Test purchasing a whole positions.
		 */
		@Test
		public void test_0020_wholePositions() {
			
			Bond[] bonds = {
				    new Bond("ACME", 50f, 10f, 0.060f),	
				    new Bond("MERC", 20f, 20f, 0.095f),	
				    new Bond("COKE", 100f, 30f, 0.020f)
				};
			Collection<Bond> investments = invest(900f, Arrays.asList(bonds));

			assertEquals(2, investments.size());
			assertEquals(900f, totalCost(investments), 0.001f);
			assertEquals(68f, totalProfit(investments), 0.001f);
		}

		/**
		 * Test purchasing a fractional position.
		 */
		@Test
		public void test_0030_fractionalPositions() {
			
			Bond[] bonds = {
				    new Bond("ACME", 50f, 10f, 0.060f),	
				    new Bond("MERC", 20f, 20f, 0.095f),	
				    new Bond("COKE", 100f, 30f, 0.020f)
				};
			Collection<Bond> investments = invest(1000f, Arrays.asList(bonds));

			assertEquals(3, investments.size());
			
			// verify costs of individual items in the portfolio.
			for (Bond bond : investments) {
				if ("ACME".equals(bond.name)) {
					assertEquals(500f, bond.totalCost(), 0f);
				}
				if ("MERC".equals(bond.name)) {
					assertEquals(400f, bond.totalCost(), 0f);
				}
				if ("COKE".equals(bond.name)) {
					assertEquals(100f, bond.totalCost(), 0.01f);
				}
			}

			assertEquals(1000f, totalCost(investments), 0.001f);
			assertEquals(70f, totalProfit(investments), 0.001f);
		}
	}
	
	/**
	 * Main program to drive unit tests.
	 * @param args unused
	 */
	@Test
	public static void main(String[] args) {
		Result result = JUnitCore.runClasses(TestInvestment.class);

		System.out.println("[Unit Test Results]");
		System.out.println();

		if (result.getFailureCount() > 0) {
			System.out.println("Test failure details:");
			for (Failure failure : result.getFailures()) {
				System.out.println(failure.toString());
			}
			System.out.println();
		}

		int passCount = result.getRunCount() - result.getFailureCount() - result.getIgnoreCount();
		System.out.println("Test summary:");
		System.out.println("* Total tests = " + result.getRunCount());
		System.out.println("* Passed tests: " + passCount);
		System.out.println("* Failed tests = " + result.getFailureCount());
		System.out.println("* Inactive tests = " + result.getIgnoreCount());
	}
		
}
