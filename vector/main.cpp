#include "vector.hpp"
// #include <vector>

// int main(void)
// {
//     ft::vector<int> vectorOnStack;
//     // ft::vector<int> vectorOnStack1(8);

//     // std::vector<int> stdVectorInts(5, 10);
//     // // std::vector<int>::iterator it;
//     // // it =  stdVectorInts.begin();
//     // std::cout << "stdVectorInts capacity: " << stdVectorInts.capacity() << '\n';
//     // stdVectorInts.reserve(1000000000000);
//     // std::cout << "stdVectorInts reserved capacity: " << stdVectorInts.capacity() << '\n';
//     return 0;
// }

int main(void)
{
    ft::vector<int> vectorOnStack;
    ft::vector<int> vectorOnStack1(8, 6);
    std::cout << vectorOnStack1.at(10) << std::endl;
    return 0;
}