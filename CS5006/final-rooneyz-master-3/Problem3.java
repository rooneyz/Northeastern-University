/**
 * Problem3.java
 * 
 * Problem 3
 * CS 5006 Final Exam
 * 
 * Given (N-1) genuine coins and 1 counterfeit coin that weights 
 * less, use only a balance scale with a balance beam and two
 * pans to detect the counterfeit coin in the smallest number of 
 * weighings. This is a reduce-and-conquer problem. 
 * 
 * If the number of coins is even, divide the coins in two piles 
 * and place them on the pans. The lighter pile contains the 
 * counterfeit coin. If odd, set one coin aside and compare the 
 * even number. If the piles are equal, the coin set aside is 
 * counterfeit. Otherwise the counterfeit coin is in the lighter 
 * pile. If only two coins remain, the lighter one is counterfeit. 
 * If there is only one coin, it must be counterfeit.
 * 
 * The number of coins decreases by a factor of 2 each time, so
 * O(log2 N) comparisons are performed, assuming that dividing 
 * the coins into two piles and weighing them are O(1) operations.
 * 
 * This problem represents the N coins as a string with (N-1) 
 * regular coin characters and 1 counterfeit coin character. 
 * Using a substring operation to divide the coins is efficient 
 * because a substring in Java does not copy characters: it just 
 * refers to the original string. Using string comparison to 
 * compare the substrings like a balance scale works because the 
 * counterfeit coin character is lexically less than the regular 
 * coin character.
 * 
 * Implement the function findCounterfeit() that takes a string 
 * representing the coins, and finds the index of the counterfeit 
 * according to the algorithm described above using only string 
 * length, substring, and string comparison to divide the coins 
 * into piles and to compare the piles like a balance scale. Do 
 * not access the value of individual coins in this function.
 * 
 * The function can be implemented iteratively or recursively. 
 * If recursively, you may use a helper function if needed.
 */

final public class Problem3 {
	/**
	 * Crate collection of (n-1) regular coins plus one light 
	 * counterfeit at the specified position in the string.
	 * 
	 * @param n number of coins
	 * @param counterfeit the index of the counterfeit coin
	 * @return collection with one light counterfeit coin.
	 */
	public static String makeCoins(int n, int counterfeit) {
		char c[] = new char[n];
		java.util.Arrays.fill(c, '1');   // regular coin
		c[counterfeit] = '0';  // counterfeit coin 
		return new String(c);
	}
	
	/**
	 * Given a collection of coins, returns the index of the
	 * counterfeit coin using only string length, substring, 
	 * and string comparison to divide the coins into piles
	 * and compare the piles with the balance scale.
	 * 
	 * @param coins the coins with one light counterfeit
	 * @return the index of the counterfeit in the string
	 */
	public static int findCounterfeit(String coins) {

		int index = 0;

		while (coins.length() >= 2){
		    // odd number
			if (coins.length() % 2 == 1) {
				int end = coins.length() - 1;
				String first = coins.substring(0, coins.length() / 2);
				String second = coins.substring((coins.length() / 2), end);
				int comp = first.compareTo(second);
				// Debug
//				System.out.println(begVal);
//				System.out.println(endVal);
				if (comp == 0) {
					index += end;
					return index;
				} else if (comp < 0) {
					coins = first;
				} else {
					coins = second;
					index += first.length();
				}

			}

			// even number of coins
			else {
				int middle = coins.length() / 2;
				String first = coins.substring(0, middle);
				String second = coins.substring(middle);
				int comp = first.compareTo(second);
				// Debug
//				System.out.println(begVal);
//				System.out.println(endVal);
				if (comp < 0) {
					coins = first;
				} else {
					coins = second;
					index += first.length();
				}
			}
		}

		return index;
	}
	
	/**
	 * Main function exercises findCounterfeit() with the
	 * counterfeit coin in each position for 1 to 7 coins.
	 * 
	 * @param args unused
	 */
	public static void main(String[] args) {
		System.out.printf("Start problem 3\n");

		// try from 1 to 7 coins
		for (int ncoins = 1; ncoins <= 7; ncoins++) {
			// repeat once for each counterfeit position 
			for (int cpos = 0; cpos < ncoins; cpos++) {
				// create the collection of coins and counterfeit
				String coins = makeCoins(ncoins, cpos);
				System.out.printf("\ncoins(%d): %s\n", coins.length(), coins);
				
				// find the counterfeit position in the string
				int found = findCounterfeit(coins);
				System.out.printf("counterfeit at: %d expected: %d\n", found, cpos);
			}
		}
		
        System.out.println("\nEnd problem 3");
	}
}