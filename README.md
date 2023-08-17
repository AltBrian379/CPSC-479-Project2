# CPSC-479 Project 2
 Project repository for CPSC 479, utilizing openMP to implement Quicksort algorithm.
 
 Brian Altamirano
 altbrian@csu.fullerton.edu
CPSC 479

Github link:
https://github.com/AltBrian379/CPSC-479-Project2

Full Project Description included in file: "CPSC-479 Project 2.pdf"

# Summary
 This program is meant to show the differences in performance between the sequential std::sort provided by the C++ standard library against a custom sort algorithm that runs in threaded parallel.
 The program utilizes the openMP library in order to implement a multithreaded algorithm.

# How it works
 The program consists of two .cpp files, main.cpp which runs the program and does the sorting and timings of both algorithms. 'parallelsort.cpp' holds the code for the custom implementation of Parallel Quicksort.

 The elements to be sorted are all randomly generated at runtime.
 
 The program accepts a flag to allow for printing the elements. This is merely for testing purposes as enabling it with a large set of numbers runs incredibly slow.

## Steps at runtime
 1. The program creates a random list of numbers and initializes it to a vector of integers, which are dynamically allocated to the heap. (The heap is preferrable as the stack has limits to memor and is more restrictive as we will be recursively implementing parallel quicksort.)
 2. The program then saves a copy of the vector for use with std::sort and quicksort.
 3. The times are measured for each sorting algorithm.

## The workings of 'parallelsort.cpp'
 In the parallel sort file we have three functions. parallelSort() is what the main() function calls. recursiveParallelSort() is where the meat of Quicksort is. CheckifAllSame() is a check to make sure the program doesn't get into a recursive loop.

 recursiveParallelSort() implements quicksort. The base condition is that if the size of the list given is 1. This is important as this means we are done breaking down the list, as is done in quicksort. There is also a check to make sure that all the elements are not all the same. If allowed, then the program would be stuck in a loop where it will continue putting lesser numbers and itself on the same list of the same size over and over again. 

The function then initializes the random number generator to determine our pivot. Then it creats two lists. One left and one right list in the heap. Using OpenMP, the program parallelizes the loop that would populate these lists using 16 threads. It first create 2 private lists corresponding to left and right. This is to make sure there is no race condition and to benefit with speedup. It then follows the quicksort algorithm.

### Pseudocode for parallelsort.cpp
```
parallelSort(list)
{
  if list is size of 1, return list
  if list is all the same elements, return the list

  Randomly select pivot

  Parallel for through all elements
   if element less than or equal to pivot
    Add to list left
   if element greater than pivot
    Add list to right
  parallelSort(left list)
  parallelSort(right list)

  Combine list left and list right

  return combined list
}
```
 
