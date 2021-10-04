#include "stack.hpp"
#include <vector>
#include <stack> //remove!!!
#include <iostream>


int main(void)
{
    ft::stack<int> testStack;

std::stack<int> stdStackInts;


    if (testStack.empty())
    {
        std::cout << "Stack is empty" << std::endl;
    }
    std::cout << "Stack's size is : [" << testStack.size() << "]." << std::endl;
    if (testStack.size() != 0)
    {
        std::cout << "std stack top is : [" << stdStackInts.top() << "]." << std::endl;
    }


    return 0;
}