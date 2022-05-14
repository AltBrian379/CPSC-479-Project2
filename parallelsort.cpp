#include "parallelsort.h"


std::vector<int>* parallelSort(std::vector<int>* list)
{
    //std::cout << "\nStarting Recursive";
    return recursiveParallelSort(list);
}

std::vector<int>* recursiveParallelSort(std::vector<int>* list)
{
    //[DEBUG] std::cout << "\nInitializing... This list is of size " << list->size() << std::endl;
    //[DEBUG] std::cout << std::endl << "Printing this List ";
	//for(auto i = 0; i < list->size(); ++i){
	///	std::cout << list->at(i) << " ";
	//}
    
    int i = 0, tid; // I for iterator and tid (probably) for thread number
    
    if(list->size() == 0) { std::cout << "\nUh how...\n"; }
    if (list->size() == 1){ 
        //[DEBUG] std::cout << "\n Size 1 conditional met\n";
         return list; } // If the size of the list is 1 return it.
    if(checkIfAllSame(list) == true) { 
        //[DEBUG]std::cout << "\n All elements in this list are the same. Returning... \n";
        return list;}

    //Random pivotS
    //std::cout << "\nCreating pivot...";
    srand( time(NULL) ); // Seed creation
    int pivot;
    pivot = (rand() % (list->size() - 1 )); // Random number generator, with limit to the size 
    // std::cout << std::endl << std::endl << "Pivot is equal to element " << pivot << " , which holds value " << list->at(pivot);

    

    // [DEBUG]std::cout << "\nAllocating memory for right and left list.";
    std::vector<int>* leftList = new std::vector<int>; // Allocate memory for the left list
    std::vector<int>* rightList = new std::vector<int>; // Allocate memory for the right list

    // [DEBUG] std::cout << "\nReserving Data for the left list: size = " << pivot+1;
    // [DEBUG] std::cout << "\nReserving Data for the right list: size = " << list->size() - (pivot + 1); 
    leftList->reserve(list->size());
    rightList->reserve(list->size());
    //std::cout << "\nBegin PragmaOMP";
    #pragma omp parallel num_threads(16) private(i, tid) shared(list,pivot, leftList, rightList) // Tell the compiler we are using 8 threads. private variables are i and tid while shared are list and pivot
    {
        std::vector<int>* privateLeftList = new std::vector<int>;
        std::vector<int>* privateRightList = new std::vector<int>;
        privateLeftList->reserve(list->size());
        privateRightList->reserve(list->size());
        #pragma omp for nowait // Parallelize the for loop
        for (i = 0; i < list->size(); ++i) // for every element in list.
        {
            
            tid = omp_get_thread_num();
            //std::cout << "\nPragmaOMP began... Working....";
            //[DEBUG] std::cout << std::endl << "I am thread #" << tid << " and I am analyzing element " << i << " with value " << list->at(i) << std::endl;
            
            if (list->at(i) <= list->at(pivot)){      // if the number at an element is less than or equal to the pivot, including the pivot 
                //printf("\nI am thread %i, analyzing element %i pushing back value %i to leftlist becuase %i <= %i",tid,i,list->at(i),list->at(i), list->at(pivot));
                privateLeftList->push_back(list->at(i));
                // add to the left list
                
            }else if(list->at(i) > list->at(pivot)){ // else if the number at an element is greater than the value of the pivot, add it to the right list
                //printf("\nI am thread %i, analyzing element %i pushing back value %i to rightlist becuase %i > %i",tid,i,list->at(i),list->at(i), list->at(pivot));
                privateRightList->push_back(list->at(i));
            }
        }

        #pragma omp critical
        {
            //std::cout << "\nHITTING CRITICAL thread " << tid;
            
                leftList->insert(leftList->end(), privateLeftList->begin(),privateLeftList->end());
            
           
                rightList->insert(rightList->end(), privateRightList->begin(), privateRightList->end());
            
            //std::cout << "\nCRITICAL DONE" << tid;
        }


        delete privateLeftList;
        delete privateRightList;





    }

    // [DEBUG] std::cout << std::endl << std::endl << "Left list size is " << leftList->size() << " and right size is " << rightList->size();

    
    
    
    //std::cout << std::endl << "Printing Left List of size " << leftList->size() << ":";
	//for(auto i = 0; i < leftList->size(); ++i){
	//	std::cout << leftList->at(i) << " ";
	//}
     //std::cout << std::endl << "Printing Right List of size " << rightList->size() << ":";
	//for(auto i = 0; i < rightList->size(); ++i){
	//	std::cout << rightList->at(i) << " ";
	//}
    //getc(stdin);

    //std::cout << "We are now entering the left list of size: " << leftList->size() << std::endl;

    if(leftList->size() == 0)
    {
        return rightList;
    }
    leftList = recursiveParallelSort(leftList); // recursively go through the left list

   // getc(stdin);
    //std::cout << "We are now entering the right list of size: " << rightList->size() << std::endl;
    if (rightList->size()== 0)
    { 
        return leftList;
    }

    rightList = recursiveParallelSort(rightList); // recursively go through the right list
    //getc(stdin);

    std::vector<int>* newList = new std::vector<int>; // declare new list pointer

    newList->reserve((leftList->size()+ rightList->size()) + 1); // allocate memory for the number of elements
    newList->insert(newList->end(), leftList->begin(), leftList->end()); // append the left side (less) first
    newList->insert(newList->end(), rightList->begin(), rightList->end()); // append the right side (greater) to the left side
     //[DEBUG]std::cout << std::endl << "Printing NewList List ";

	//[DEUBUG]for(auto i = 0; i < newList->size(); ++i){
	//	std::cout << newList->at(i) << " ";
	//}
    
    delete rightList;
    delete leftList;
    
   
    

    return newList; // return the newly formed list. 
}


bool checkIfAllSame(std::vector<int>* list)
{
    int i, val;
    val = list->at(0);
    
    bool check = true;

     #pragma omp parallel num_threads(8) private(i) shared(list,val, check) // Tell the compiler we are using 8 threads. private variables are i and tid while shared are list and pivot
    {

        #pragma omp for // Parallelize the for loop
        for (i = 0; i < list->size(); ++i) // for every element in list.
        {
            if(list->at(i) != val){
                check = false;
            }
            
           
        }


    }
    return check;
    

}