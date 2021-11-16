# Grading for assignment-5-rooneyz
**Class:** 2019S1CS5007SV<br>
**Date:** 2019-06-02<br>
**Grader:** Jasmine Wei 

## Total: 59/60
## Comments

Remove 1 point
Dealer() has no need to sleep for 2 seconds, since the resource will be locked and pthread_cond_wait will wait.
And try to use dealt_card != NO_CARD rather than 0, since it's hard for others to understand with is 0. Don't use magic number.
