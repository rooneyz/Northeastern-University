/**
 * Investment.java
 * 
 * This program selects an optimal investment portfolio
 * using a greedy algorithm that prioritizes the most
 * shares of the highest yielding bond first.
 * 
 */
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Comparator;
import java.util.PriorityQueue;

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
	static public final class Bond {
		/** Name of the bond */
		final public String name;
		/** Number of shares */
		final public float shares;
		/** Cost per share */
		final public float cost;
		/** Yield as a percentage (0.06 = 6%) */
		final public float yield;
		
		/**
		 * Create a bond instance.
		 * @param name name of the bond
		 * @param shares number of shares available
		 * @param cost cost per share
		 * @param yield yield as a percentage (0.06 = 6%)
		 */
		public Bond(String name, float shares, float cost, float yield) {
			this.name = name;
			this.shares = shares;
			this.cost = cost;
			this.yield = yield;
		}
		/**
		 * Returns the total cost of the bond
		 * @return total cost (shares * cost)
		 */
		public float totalCost() {
			return shares * cost;
		}
		/**
		 * Returns the total profit on the bond
		 * @return total profit (totalCost * yield)
		 */
		public float totalProfit() {
			return totalCost() * yield;
		}
		
		/**
		 * Simple representation for testing purposes
		 */
		public String toString() {
			return name + " | " + shares + " @ " + cost + " / " + yield;
		}
	}
	
	/**
	 * This class orders bonds from highest to lowest yield.
	 */
	static class HighestBondYieldComparator implements Comparator<Bond> {
		public int compare(Bond bond1, Bond bond2) {
			// reverse to get highest to lowest ordering
			return Float.compare(bond2.yield, bond1.yield);
		}
	}

	/**
	 * Returns the optimum list of bonds from a bond priority queue.
	 * @param total total amount available to invest
	 * @param bonds collection of investment opportunities
	 * @return a portfolio of bonds
	 */
	static Collection<Bond> invest(float total, Collection<Bond> bonds) {
		PriorityQueue<Bond> bondsQueue = 
			new PriorityQueue<>(bonds.size(), new HighestBondYieldComparator());
		bondsQueue.addAll(bonds);
		
		Collection<Bond> investments = new ArrayList<Bond>();
		float available = total;
		
		while (!bondsQueue.isEmpty()) {
			if (available < 0.001) {  // done if less that 1 cent
				break;
			}
			Bond bond = bondsQueue.poll();
			if (available >= bond.totalCost()) {
				// purchase entire position of this bond
				investments.add(bond);
				available -= bond.totalCost();
			} else {
				// purchase partial position of this bond
				float shares = available / bond.cost;
				Bond partialBond =
					new Bond(bond.name, shares, bond.cost, bond.yield);
				investments.add(partialBond);
				available -= partialBond.totalCost(); 
			}
		}
		return investments;
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
