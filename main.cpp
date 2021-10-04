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
        std::cout << "The Stack is empty" << std::endl;
    }
    else
    {
         std::cout << "Stack's size is : [" << testStack.size() << "]." << std::endl;
    }

    if (testStack.size() != 0)
    {
        std::cout << "std stack top is : [" << testStack.top() << "]." << std::endl;
    }
    testStack.push(5);
    std::cout << "The element added: [" << testStack.top() << "]." << std::endl;
    
    if (testStack.empty())
    {
        std::cout << "The Stack is empty" << std::endl;
    }
    else
    {
         std::cout << "Stack's size is : [" << testStack.size() << "]." << std::endl;
    }
    testStack.push(500000);
    std::cout << "The element added: [" << testStack.top() << "]." << std::endl;
    testStack.push(-90);
    std::cout << "The element added: [" << testStack.top() << "]." << std::endl;
    testStack.push(3222);
    std::cout << "The element added: [" << testStack.top() << "]." << std::endl;
    testStack.push(0);
    std::cout << "The element added: [" << testStack.top() << "]." << std::endl;
    testStack.push(-333334440);
    std::cout << "The element added: [" << testStack.top() << "]." << std::endl;
    if (testStack.empty())
    {
        std::cout << "The Stack is empty" << std::endl;
    }
    else
    {
         std::cout << "Stack's size is : [" << testStack.size() << "]." << std::endl;
    }
    testStack.pop();
    std::cout << "Stack's size is : [" << testStack.size() << "]." << std::endl;
    testStack.pop();
    std::cout << "Stack's size is : [" << testStack.size() << "]." << std::endl;
    testStack.pop();
    std::cout << "Stack's size is : [" << testStack.size() << "]." << std::endl;
    testStack.pop();
    std::cout << "Stack's size is : [" << testStack.size() << "]." << std::endl;
    testStack.pop();
    std::cout << "Stack's size is : [" << testStack.size() << "]." << std::endl;
    testStack.pop();
    if (testStack.empty())
    {
        std::cout << "The Stack is empty" << std::endl;
    }
    else
    {
         std::cout << "Stack's size is : [" << testStack.size() << "]." << std::endl;
    }

    return 0;
}