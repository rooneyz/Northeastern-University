# Final exam information and problem descriptions for CS 5006

## About the Exam
 
This exam consists of five (5) problems.  You must implement solutions for problems 1 and 2, and also solve one (1) selected from problems 3 through 5. The problems are located in a repository 2019S2CS5006SV/final-*ccis-id* for your CCIS ID. 
 
Each problem is in a file named for the problem. Problem 1 is a text file that you can edit in place with your answers. For problems 2-5 the source code file includes a main program that calls the function(s) for the algorithm you will implement. You may define additional functions or classes if necessary, but you may not modify the main program. Your entire solution must be in the single source code file for the problem, which you will submit by checking the source code file back in to the repository.
 
Use the language corresponding to the source code file.  Be sure to include sufficient internal documentation for the graders to understand your implementation.
 
## Test Conditions
 
The exam will begin at 4pm on Tuesday August 20th, and you must turn in your solutions no later than 9.30pm.  You may bring food or beverages to consume during the exam. You may take bio breaks as required.
 
You may use any resources including your notes, the course website, and other online resources. You are on your honor not consult with anyone about the questions or solutions by any means during the exam period. The instructor will answer any questions privately during the exam and may also offer hints or suggestions solely at the instructor's discretion.
 
## Summary of Test Questions
 
1. This problem presents a Java function that implements an algorithm for counting the number of duplicate entries in an array. Your task is to analyze this algorithm and determine the characteristic g(n) for the best and worst case input, state and prove the time complexity Θ(g(n)) for each, and provide sample input that exhibits the best and worst case behavior. You will also be asked to compare this algorithm to one that is optimized for a sorted array.
 
2. A non-tail recursive Java function _power_nt()_ computes the non-negative n-th intger power of a floating point number. This problem is to implement a tail-recursive version of the function based on the non-tail recursive version, and an interative version from the tail recursive version based on the tail-recursive version, using the transformation techniques presented in class.  The problem will be graded entirely on your ability to demonstrate the application of these techniques. Include descriptions in the function headers of how you applied these techniques.
 
3. Given a pile of (N-1) genuine coins and 1 counterfeit coin that weights less, a balance scale with a balance beam and two pans can be used to detect the counterfeit coin using a greedy reduce-and-conquer algorithm in the smallest number of weighings.  This problem is to implement the algorithm as a Java function _findCountfeit()_ using a string representation of the coins, string comparison as a balance to compare piles of coins, and string length and substring operations to divide the coins into piles.

4. Given an even power-of-2 size array, the problem is to write a Java function _shuffleArray()_ that shuffles together the lower and upper sub-arrays in place without using an auxilliary array. The algorithm described is based on divide and donquer because at each step it partitions the problem and works all of the parts. Provide a recursive implementation of the algorithm.

5. Every positive rational number can be represented as a whole number plus a sum of fractions whose numerator is 1 and whose denominator is a positive whole number, such as 1/3. This problem is to implement a Java function _printFractions()_ that takes a non-negative integer numerator and deniminator, and prints the terms of the sum on a line. For 7/5, the function would print "1 + 1/3 + 1/15" and for 6//14 it would print "1/3 + 1/11 + 1/231".

