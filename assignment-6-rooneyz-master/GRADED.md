# Grading for assignment-6-rooneyz
**Class:** 2019S1CS5007SV<br>
**Date:** 2019-06-18<br>
**Grader:** Mark Kachur

## Total: 49/60
## Comments

-3 Missing logic to take socket number as program argument

-3 By keeping your loop always running you are not allowing your program to finish. And depending on the system the socket will stay in use. You need to think of a way to send a signal to your program to tell it to finish, that would allow you to close the socket freeing the resources for other programs. (and allowing multiple runs of the same program)

-5 Your paidrome prints everything in the arrays each time, so if you have a longer palindrome first, and the next on is shorter then it will print the short string, then the middle of the other string, then the rest of the short string. (try setting the buffers you read the input into to 0 each time to reset them)

You also dont need to add a new line character as no palindrome has a new line in the middle of it.

