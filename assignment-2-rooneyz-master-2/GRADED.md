# Grading for assignment-2-rooneyz
**Class:** 2019S1CS5007SV<br>
**Date:** 2019-05-12<br>
**Grader:** Jasmine 

## Total: 48/50
## Comments

-1    
Missing asserts and if conditions to make sure that fseek and fwrite do work in getDictionaryDefinition and putDictionaryEntry. In assignment description, it requires you to check return values. And in your code, you are calling fseek and fwrite without checking their return values. Although they work here, they might fail under other circumstances. Having those conditions might make it easier to debug.

-1    
Missing comments. A proper coding style will help others understand your code efficiently. And do check Phil's answer or his lecture codes out to get used to the coding format in C/Java, adding comments for block of code. 
