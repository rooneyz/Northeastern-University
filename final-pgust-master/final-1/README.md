I was experimenting with some changes to the files in the "files" directory
after capturing the expected output for the two problems, and neglected to
restore the tree to its original state before checking them in.  Given the
data files distributed with this question for the final exam, the expected
output of the two questions should be:

```
final-1a.bash:

Line counts for '.txt' files
expected:
       7 files/a/b/d/h/X.txt
       7 a/b/d/h/X.txt
       6 files/a/b/X.txt
       6 a/b/X.txt
       5 files/a/c/f/m/X.txt
       5 a/c/f/m/X.txt
       4 files/a/c/g/n/X.txt
       4 files/a/X.txt
       4 a/c/g/n/X.txt
       4 a/X.txt
       3 files/a/c/X.txt
       3 a/c/X.txt

Line counts for all files
expected:
       7 files/a/b/d/h/X.txt
       7 a/b/d/h/X.txt
       6 files/a/b/X.txt
       6 a/b/X.txt
       5 files/a/c/g/o/O
       5 files/a/c/f/m/X.txt
       5 a/c/g/o/O
       5 a/c/f/m/X.txt
       4 files/a/c/g/n/X.txt
       4 files/a/X.txt
       4 a/c/g/n/X.txt
       4 a/X.txt
       3 files/a/c/X.txt
       3 files/a/b/e/E
       3 a/c/X.txt
       3 a/b/e/E
       2 files/a/c/g/G
       2 a/c/g/G
       1 files/a/c/C
       1 files/a/A
       1 files/.DS_Store
       1 a/c/C
       1 a/A
```
```
final-1b.bash:

Word counts for files that contain 'cricket'
expected:

Word counts for files that contain 'none'
expected:
   2 seven
   4 six
   8 five
  12 four
  16 one
  16 three
  16 two
  74 none

Word counts for files that contain 'ladybug'
expected:
   2 bluejay
   4 butterfly
   4 hummingbird
   6 ladybug
   8 bumblebee

Word counts for files that contain 'bumblebee'
expected:
   1 bumblebeeflight
   2 bluejay
   2 bumblebees
   2 fly
   3 flying
   4 butterfly
   4 hummingbird
   6 ladybug
  64 of
  64 the
  74 flight
  85 bumblebee
```
