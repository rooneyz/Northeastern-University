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
		// your code here
	}
	
	/**
	 * This class orders bonds from highest to lowest yield.
	 */
	static class HighestBondYieldComparator implements Comparator<Bond> {
		public int compare(Bond bond1, Bond bond2) {
			// your code here
		}
	}

	/**
	 * Returns the optimum list of bonds from a bond priority queue.
	 * @param total total amount available to invest
	 * @param bonds collection of investment opportunities
	 * @return a portfolio of bonds
	 */
	static Collection<Bond> invest(float total, Collection<Bond> bonds) {
		// your code here
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
