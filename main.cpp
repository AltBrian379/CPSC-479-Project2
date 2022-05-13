/*=============================================
Requirements:
1. [DONE]Function that creates a list of random numbers
2. [DONE] function that tests the speed of std::sort
3. function that tests the speed of our own sorting algorithm
4. CLass of our sorting algorithm, takes in a vector of random numbers.
5. [DONE]Program takes input of the amount of numbers.

==============================================*/


#include <iostream>
#include <omp.h>
#include <vector>
#include "time.h"
#include <algorithm>
#include <stdlib.h>
#include <cstring>

// Custom files
#include "parallelsort.h"

std::vector<int> * createRandomNumbers(int);

void runSTDSort(std::vector<int>*,int);

int main(int argc, const char* argv[]){

	// Parsing parameters
	bool print = false;
	int inputamount;

	for(auto i = 1; i < argc; ++i)
	{
		if (strcmp(argv[i], "-p") == 0){
			print = true;
		}
		
		if(argv[i][0] != '-')
		{
			inputamount = atoi(argv[i]);
			if(inputamount <= 0){
				std::cout << "ERROR: Zero and Negative Numbers are not Allowed!";
				return 0;
			}
		}

	}

	if (print)
	{
		std::cout <<std::endl << "Printing is enabled..." << std::endl;
	}
	// End of Parsing Parameters

	// List to hold random numbers
	std::vector<int> * myList;
	

	std::cout << "Program Starting... input = " << inputamount << std::endl << std::endl;
	myList = createRandomNumbers(inputamount);

	std::vector<int> * myListCopy = new std::vector<int>;

	myListCopy->reserve(myList->size());
	myListCopy->insert(myListCopy->end(),myList->begin(),myList->end());

	//[DEBUG]std::cout << std::endl << "Size of copy: " << myListCopy->size() << std::endl;



	if(print){
		// Printing initially created list.
		std::cout << "Initial list: ";
		for(auto i = 0; i < inputamount; ++i){
			std::cout << myList->at(i) << " ";
		}
	}

	// Running STD Sort.
	runSTDSort(myList, inputamount);

	if(print){
		// Printed using STD Sort
		std::cout << std::endl << "Sorted list (std::sort()): ";
		for(auto i = 0; i < inputamount; ++i){
			std::cout << myList->at(i) << " ";
		}
	}

	// Running my Quicksort
	time_t start, end;
	start = clock();
	std::cout << "\nWe are starting my Quicksort...";
	 myListCopy = parallelSort(myListCopy);
	std::cout << "\nWe are ending my Quicksort...";
	end = clock();

	double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	std::cout << std::endl << "Parallel Quicksort total time: " << cpu_time_used << std::endl << std::endl;

	if(print){
		std::cout << std::endl << "Sorted list (Custom QuickSort): ";
		for(auto i = 0; i < myListCopy->size(); ++i){
			std::cout << myListCopy->at(i) << " ";
		}
	}

	

	delete myList;
	delete myListCopy;

	return 0;
}


std::vector<int>* createRandomNumbers(int amount){
	std::cout << "We are creating " << amount << " random numbers for sorting!\n";

	srand(time(NULL));

	std::vector<int> * list = new std::vector<int>;


	for (auto i = 0; i < amount; ++i)
	{
		int x = std::abs(rand() % 100);
		list->push_back(x);
	}

	return list;
}



void runSTDSort(std::vector<int>* list, int inputamount)
{
	time_t start, end;

	std::cout << std::endl << std::endl << "Sorting using std::sort()...";
	start = clock();
	std::sort(list->begin(), list->end() );

	end = clock();

	double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	std::cout << std::endl << "std::sort total time: " << cpu_time_used << std::endl << std::endl;
	// End of Standard Library Sorting

}