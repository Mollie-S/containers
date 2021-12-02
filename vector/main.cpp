#include "vector.hpp"
// #include <vector>

int main(void)
{
    // ft::vector<int> vectorOnStack1(8);

    // std::vector<int> stdVectorInts(5, 10);
    // std::vector<int>::iterator it;
    // it =  stdVectorInts.begin();
    // std::cout << "stdVectorInts capacity: " << stdVectorInts.capacity() << '\n';
    // stdVectorInts.reserve(1000000000000);
    // std::cout << "stdVectorInts reserved capacity: " << stdVectorInts.capacity() << '\n';

    int intArray[] = { 1, 2, 9, 10, 11, 12, 13, 14};
    size_t arraySize = sizeof(intArray)/ sizeof(intArray[0]);
    ft::vector<int> myVect(intArray, intArray + arraySize);
    ft::vector<int>::iterator it;
    // for (it = myVect.begin(); it != myVect.end(); ++it) {
    ft::vector<int>::iterator end = myVect.begin() + arraySize;
    for (it = myVect.begin(); it != end; ++it)
    {
        std::cout << *it << std::endl;
    }

    return 0;
} 

