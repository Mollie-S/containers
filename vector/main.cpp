#include "vector.hpp"
#include <vector>

int main(void)
{
    ft::vector<int> vectorOnStack;
    // ft::vector<int> vectorOnStack(8);

    std::vector<int> stdVectorInts(5, 10);
    std::vector<int>::iterator it;
    it =  stdVectorInts.begin();
    stdVectorInts.reserve(10000000000000000000);


}