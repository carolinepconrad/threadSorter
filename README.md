# [CIS 321 - Operating Systems | Cairn University]

The purpose of the program is to use pthreads to read input from multiple files,
process the data, and sort it from least to greatest, and then write it to an output.
In this program, I created a function work() to open and read a file, and to scan the numbers
in the file if there are any and then print it in ascending order using qsort(). I also created
5 threads for this program, that each process a file concurrently. The pthread_join is used to
wait for the completion of each thread.

