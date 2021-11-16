#!/bin/bash
##
# final-1b.bash
#
# This program tests function count_unique_words_in_files()
# that outputs an aggregate list of all words and their
# frequencies for files that contain a specific word or
# phrase in the current directory hierarchy. 
#
# This program utilizes the accompanying "files" directory
# and must be run in the directory that contains "files".


##
# Output list of files in that contain a specific word or 
# phrase in the current directory hierarchy, one per line.
# @param $1 the word or phrase
find_files_with_words() {
	grep -l -R "$1" *
}


## 
# Reads list of files from standard input, one per line
# and cats the contents of the files.
cat_files() {
	while read -r line; do 
		cat "$line" 
	done
}
##
# Output a list of words and their frequencies for all 
# files that contain a specific word or phrase in the 
# current directory hierarchy, in ascending frequency.
# A word is delimited by one or more whitespaces.
# @param $1 the word or phrase
count_unique_words_in_files() {
	find_files_with_words "$1" | cat_files | tr -s '[:space:]' '\n' | sort | uniq -c | sort -n
}

echo "Start final-1b"

echo
echo "Word counts for files that contain 'cricket'"
(cd files && count_unique_words_in_files cricket)
echo "expected:"

echo
echo "Word counts for files that contain 'none'"
(cd files && count_unique_words_in_files none)
echo "expected:"
cat <<- EOF
   1 seven
   2 six
   4 five
   6 four
   8 one
   8 three
   8 two
  37 none
EOF

echo
echo "Word counts for files that contain 'ladybug'"
(cd files && count_unique_words_in_files ladybug)
echo "expected:"
cat <<- EOF
   1 bluejay
   2 butterfly
   2 hummingbird
   3 ladybug
   4 bumblebee
EOF

echo
echo "Word counts for files that contain 'bumblebee''"
(cd files && count_unique_words_in_files bumblebee)
echo "expected:"
cat <<- EOF
   1 bluejay
   2 butterfly
   2 hummingbird
   3 ladybug
  32 flight
  32 of
  32 the
  36 bumblebee
EOF

echo
echo "End final-1b"
