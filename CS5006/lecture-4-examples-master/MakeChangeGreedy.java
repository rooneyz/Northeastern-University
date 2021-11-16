import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.ArrayList;
import java.util.TreeSet;

/**
 * Demonstration of greedy algorithm for making channge.
 * 
 * @author philip gust
 */
public final class MakeChangeGreedy {
	/**
	 * This class implements a set of coin denominations in descending order.
	 */
	@SuppressWarnings("serial")
	public static final class CoinSet extends TreeSet<Integer> {
		/**
		 * Descending set of coin denominations
		 * 
		 * @param values the values to initialize set
		 */
		public CoinSet(Integer ... values) {
			this(Arrays.asList(values));
		}

		/**
		 * Descending set of coin denominations
		 * 
		 * @param values a collection of values to initialize set
		 */
		public CoinSet(Collection<Integer> values) {
			super(Collections.reverseOrder());
			addAll(values);
		}
	}
	
	/**
	  * Greedy algorithm makes change for amount using coin denominations.
	  * 
	  * @param amount the amount for which to make change
	  * @param coins set of coin denominations in descending order
	  * @return collection of coins that make change for amount
	  */
	static public Collection<Integer> makeChange(int amount, CoinSet coins) {
		Collection<Integer> change = new ArrayList<>();  // result list
		for (int coin : coins) {	// select each coin in coin set
			while (amount >= coin) {
				change.add(coin);  // add as many of coin denomination as possible
				amount -= coin;
			}
		};

		return change;
	}

	/**
	 * Print change for a given amount.
	 * 
	 * @param amount the amount for which to make change
	 * @param change collection of coins
	 */
	public static void printChange(int amount, Collection<Integer> change) {
		System.out.printf("Change for %d cents:", amount);
		if (change.isEmpty()) {
			System.out.print(" none");
		} else {
			change.forEach((coin) ->
				System.out.printf(" %d", coin)
			);
		}
		System.out.println();
	}

	/**
	 * Makes change for specific amounts using denominations of U.S. coins.
	 * 
	 * @param args unused
	 */
	public static void main(String[] args) {
		// set of coin denominations, highest to lowest
		CoinSet coins = new CoinSet(100, 50, 25, 10, 5, 1);
		
		int amount = 191;
		Collection<Integer> change = makeChange(amount, coins);
		printChange(amount, change);

		amount = 34;
		change = makeChange(amount, coins);
		printChange(amount, change);

	}
}
