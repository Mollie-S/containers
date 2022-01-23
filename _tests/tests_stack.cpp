#include "tests.hpp"

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};


void stack_test()
{
    std::cout << "\n\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "|                STACK                  |\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "The Mutant Stack behavior. Mutant Stack is the iterable stack:"<< std::endl;
    MutantStack<int> mutant;
    if (mutant.empty())
    {
        std::cout << "The stack is empty" << std::endl;   
    }
    std::cout << "Adding a new element:" << std::endl;
    mutant.push(5);
    std::cout << "The element at the top of the stack: " << mutant.top() << std::endl;
    std::cout << "Adding a new element:" << std::endl;
    mutant.push(17);
    std::cout << "The element at the top of the stack: " << mutant.top() << std::endl;
    std::cout << "The stack's size: " << mutant.size() << std::endl;
    std::cout << "Adding a new element:" << std::endl;
    mutant.push(-89);
    std::cout << "The element at the top of the stack: " << mutant.top() << std::endl;
    std::cout << "The stack's size: " << mutant.size() << std::endl;
    std::cout << "Removing an element:" << std::endl;
    mutant.pop();
    std::cout << "The stack's size: " << mutant.size() << std::endl;
    std::cout << "\nAdding more elements(view the code)."<< std::endl;
    mutant.push(3);
    mutant.push(5);
    mutant.push(737);
    mutant.push(0);
    mutant.push(0);
    mutant.push(0);
    mutant.push(0);
    mutant.push(0);
    mutant.push(92735729);
    std::cout << "The stack's size: " << mutant.size() << std::endl;

    std::cout << "Iterating the stack:"<< std::endl;
    MutantStack<int>::iterator it = mutant.begin();
    MutantStack<int>::iterator ite = mutant.end();
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }
    std::cout << "\n";
    

    ft::stack<int, ft::vector<int> > s;
    if (s.empty())
    {
        std::cout << "The stack is empty" << std::endl;   
    }
}
