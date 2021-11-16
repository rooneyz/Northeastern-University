CS 5006 Summmer2 2019 Assignment 1

Philip Gust

1. Suppose we are choosing between two algorithms for a particular computational task. One takes f1(n) = n<sup>2</sup> steps, while the other takes f2(n) = 2n + 20 steps. What is the big-O for each of these? Which is better and why?

For f1(n) = n<sup>2</sup>, g(n) = n<sup>2</sup> because for c=1, n<sup>2</sup> >= n<sup>2</sup> for n<sub>0</sub> = 1, so the big-O for f1(n) is O(n<sup>2</sup>).
For f2(n) = 2n + 20, g(n) = n because for c=3, 3n >= 2n+20 for n<sub>0</sub>=20, so The big-O for f2(n) is O(n). 

Function f2 is better because it has a lower time complexity than f1.

2. A function finds the largest and the smallest values in an unsorted array. Show the f(n) for this function, and use the definition of big-O to show that f(n) is O(n).

Finding the largest and the smallest values can both be done by scanning through the array once and at each value recording the largest and smallest item found so far. Therefore the algorithm is f(n) = 2n + k, so g(n) = n because for c=3, 3n >= 2n+k for n<sub>0</sub> = k. Therefore the compelexity is O(n). 

3. We saw that the bubble sort algorithm shown in class is O(n<sup>2</sup>). Suppose that we add a test that exits the algorithm early if there are no swaps in the inner loop for a given iteration of the outer loop. 

a) Show the f(n) and the big-O for this modified algorithm.

f(n) remains kn<sup>2</sup> + O(1) in the worst case of a reverse-sorted input array where there will be an exchange every time through the inner loop, so the big-O is still O(n<sup>2</sup>). However in the best case of a forward-sorted array, the outer loop executes only once and the inner loop executes n times, so f(n) = kn + O(1) and the best case time order is O(n).

b) Does the modification change the big-O for this algorithm?
The modification does not change the big-O for this function in the worst case, but goes from O(n<sup>2</sup>) to O(n)  for the best case. 

4. The formula for factorial(n) or n! is:
factorial(0) = 1
factorial(n) = n * factorial(n-1)  (n>0)
			
Use the definition of big-O to show that the big-O for factorial(n) is O(n). 

At each level of recursion, a single value multiplies the results of the next level, so, each value is considered only once. Therefore f(n) = k<sub>1</sub>n + k<sub>0</sub> and g(n) = n for c = k<sub>1</sub>+1 and for n<sub>0</sub> = k<sub>0</sub>, so the big-O is O(n). 
