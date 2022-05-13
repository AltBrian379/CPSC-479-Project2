#include <vector>
#include <stdlib.h>
#include <omp.h>
#include <stdlib.h>
#include <ctime>
#include <iostream>

std::vector<int>* parallelSort(std::vector<int>*);

std::vector<int>* recursiveParallelSort(std::vector<int>*);
bool checkIfAllSame(std::vector<int>*);