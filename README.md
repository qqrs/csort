## c-sorting

Sorting algorithms in C with a test framework.

### Usage

`./csort`  
Run tests for all sorting algorithms

`./csort benchmark`  
Benchmark all sorting algorithms using `clock_gettime
CLOCK_PROCESS_CPUTIME_ID`. Prints actual time  and time relative to stdlib
qsort.

`./csort <algorithm> <data>`  
Runs a sorting algorithm on user-supplied data.  
`<data>` is a list of integers to be sorted.   
`<algorithm>` specifies the sorting algorithm to use:
quicksort, quicksort2, mergesort, heapsort, inssort, inssort2, inssort3, bubblesort, bubblesort2 


### TODO
* Convert all sorting algorithms to use stdlib `qsort()` style function signature (i.e., arbitrary element size and comparison function) to allow direct comparison between algorithms.
  
* Command line parameters: benchmark test case size, number of
  trials to be averaged 

