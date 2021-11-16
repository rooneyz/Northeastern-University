# Grading for assignment-4-rooneyz
**Class:** 2019S1CS5007SV<br>
**Date:** 2019-05-29<br>
**Grader:** LUNA

## Total: 60/60
## Comments
The difference between your output and the expected output is that your "Waiting for 3 threads to terminate" message comes after the threads terminate. This can be solved by changing your ManageThreads() function. In your timeslice "for loop" you can insert the running variable in the second parameter of the for loop, as such:

       for (unsigned int time = 0; running && time < timeslice; time++) {
		  	sleep(1);
		      }

By putting the running variable directly into this loop you make sure the threads terminate at precisely the right time. Try adding this to your code! 

I did not remove any pooints for this :)


GREAT WORK
