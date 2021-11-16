#!/bin/bash

##
# final-1b.bash
#
# This program tests function count_unique_lines_in_files() 
# that outputs an aggregate list of words and frequencies
# for all files in the currrent directory hierarchy that 
# contain a specific word or phrase phrase. Implement and
# use the supporting function as part of the solution. 
#
# This program utilizes the accompanying "files" directory
# and must be run in the directory that contains "files".

##
# Reads file names, one per line from standard input, and
# outputs a count of the number of unique lines and the 
# file path for each file, one per line.
get_unique_line_counts_in_files() {
	while read fname; do
		local count=$(sort -u "$fname" | wc -l)
		printf "%8d %s\n" $count "$fname"
	done
}

##
# Outputs line counts and file paths for all regular files 
# in the current directory with the specified file extension,
# or of all files if not specified. Output is in descending
# count order. Correctly handles file paths with spaces.
# @param $1 the file type (e.g. '.txt') (default: all files)
count_unique_lines_in_files() {
	find * -type f -name "*$1" | get_unique_line_counts_in_files | sort -nr 
}

echo "Start final-1a"

echo 
echo "Line counts for '.html' files"
(cd files && count_unique_lines_in_files .html)
echo "Expected:"
cat <<- EOF
EOF

echo 
echo "Line counts for '.txt' files"
(cd files && count_unique_lines_in_files .txt)
echo "Expected:"
cat <<- EOF
       7 a/b/d/h/X.txt
       5 a/c/f/m/X.txt
       4 a/X.txt
       3 a/c/X.txt
       2 a/c/g/n/X.txt
       1 a/b/X.txt
EOF

echo 
echo "Line counts for all files"
(cd files && count_unique_lines_in_files)
echo "Expected:"
cat <<- EOF
       7 a/b/d/h/X.txt
       5 a/c/g/o/O
       5 a/c/f/m/X.txt
       4 a/X.txt
       3 a/c/X.txt
       3 a/b/e/E
       2 a/c/g/n/X.txt
       2 a/c/g/G
       1 a/c/C
       1 a/b/X.txt
       1 a/A
EOF

echo
echo "End final-1a"
