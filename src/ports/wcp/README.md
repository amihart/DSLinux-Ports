# wc command in C
A simple implementation of the linux wc command using C Language.There may be some bugs in the program,you are encouraged to fix them.

Compile:  wcp.c - cc wcp.c -o wcp 
                                                     
                                                     User Commands                                                                 


NAME

        ./wcp - print newline, word, and byte counts for each file

SYNOPSIS
        
        ./wcp [OPTION]... [FILE]...
        ./wcp [OPTION]... --files0-from=F

DESCRIPTION
 
       Print  newline,  word,  and  byte counts for each FILE, and a total line if more than one FILE is specified.  With no FILE, or when FILE is -, read standard input.  A word is a non-zero-length sequence of characters delimited by white space.  The options below may be used to select which counts are printed, default order: newline, word, character, byte, maximum line length.

       -c, --bytes
              print the byte counts

       -m, --chars
              print the character counts

       -l, --lines
              print the newline counts

       --files0-from=F
              read input from the files specified by NUL-terminated names in file F; If F is - then read names from standard input

       -L, --max-line-length
              print the length of the longest line

       -w, --words
              print the word counts

       --help display this help and exit

       --version
              output version information and exit
