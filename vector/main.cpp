#include "vector.hpp"
#include <vector>

int main(void)
{
    // ft::vector<int> vectorOnStack1(8);
// 
//     std::vector<int> stdVectorInts(5, 10);
//     std::vector<int>::iterator it;
//     it =  stdVectorInts.begin();
//     std::cout << "stdVectorInts capacity: " << stdVectorInts.capacity() << '\n';
//     // stdVectorInts.reserve(1000000000000);
//     stdVectorInts.insert(it + 1, 20, 1000);
//     std::cout << "stdVectorInts reserved capacity: " << stdVectorInts.capacity() << '\n';

    // int intArray[] = { 1, 2, 9, 10, 11, 12, 13, 14};
    // size_t arraySize = sizeof(intArray)/ sizeof(intArray[0]);
    // ft::vector<int> myVect(intArray, intArray + arraySize);
    // ft::vector<int>::iterator it;
    // // for (it = myVect.begin(); it != myVect.end(); ++it) {
    // ft::vector<int>::iterator end = myVect.begin() + arraySize;
    // for (it = myVect.begin(); it != end; ++it)
    // {
    //     std::cout << *it << std::endl;
    // }

    int intArray[] = { 20000, 2, 9, 10, 11, 0, 0, 0, 0, 0, 12, 13, 14, 89};
        size_t arraySize = sizeof(intArray)/ sizeof(intArray[0]);
        ft::vector<int> ftVectorInts(intArray, intArray + arraySize);
        std::vector<int> stdVectorInts(intArray, intArray + arraySize);
        ft::vector<int>::iterator ftIt = ftVectorInts.begin();
        std::vector<int>::iterator stdIt  = stdVectorInts.begin();
        std::cout << "my initioal capacity: "<< ftVectorInts.capacity() << std::endl;
        std::cout << "std initioal capacity: "<< stdVectorInts.capacity() << std::endl;
        std::cout << "my initial size: "<< ftVectorInts.size() << std::endl;
        std::cout << "std initial size: "<< stdVectorInts.size() << std::endl;
        ftVectorInts.erase(ftIt + 5, ftIt + 10);
        stdVectorInts.erase(stdIt + 5, stdIt + 10);
        std::cout << "my : "<< *(ftVectorInts.end() - 1) << std::endl;
        std::cout << "std : "<< *(stdVectorInts.end() - 1) << std::endl;
        std::cout << "my : "<< ftVectorInts.size() << std::endl;
        std::cout << "std : "<< stdVectorInts.size() << std::endl;
        std::cout << "my : "<< ftVectorInts.capacity() << std::endl;
        std::cout << "std : "<< stdVectorInts.capacity() << std::endl;
        std::cout << "UPDATED VECTOR_____________________________" << std::endl;
            for (std::vector<int>::iterator it = stdVectorInts.begin(); it != stdVectorInts.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    return 0;
} 

