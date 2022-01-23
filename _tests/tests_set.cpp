#include "tests.hpp"

template <typename T>
void print_set(const ft::set<T>& s)
{
    typename ft::set<T>::const_iterator f_it = s.begin();
    typename ft::set<T>::const_iterator itEnd = s.end();
    std::cout << "The set looks like this:\n";
    if (s.empty())
    {
        std::cout << "The set is empty\n";
    }
    for (typename ft::set<T>::const_iterator i = f_it; i != itEnd; ++i)
    {
        std::cout  << "Key: " << *i << std::endl;
    }
    std::cout  << "Size: " << s.size() << std::endl;
    std::cout <<"--------------------------------------------------"<<  std::endl;
}

void set_test()
{
	const char *args[] = {"black", "white", "pink", "purple", "turquoise", "beige", "grey", "maroon", "coral", "orange", "khaki", "fuchsia"};
	size_t length = sizeof(args) / sizeof(args[0]);

	std::cout << "\n\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "|                SET                    |\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "Creating an empty set and inserting the range of values." << std::endl;
	ft::set<std::string> my_set;
	my_set.insert(args, args + length);
	print_set(my_set);
    std::cout << "Count() function for the existing argument 'pink' returns " << my_set.count("pink")<< std::endl;
    std::cout << "Count() function for the non-existing argument 'gold' returns " << my_set.count("gold")<< std::endl;
    std::cout << "ITERATORS:" << std::endl;
    std::cout << "The value of the element accessed by begin() is " << *my_set.begin() << std::endl;
    std::cout << "The value of the element accessed by rbegin() is " << *my_set.rbegin() << std::endl;
	ft::set<std::string>::iterator it_e = my_set.end();
	ft::set<std::string>::reverse_iterator r_it_e = my_set.rend();
	it_e--;
	r_it_e--;
	std::cout << "The value of the element accessed by end() is " << *it_e << std::endl;
	std::cout << "The value of the element accessed by end() is " << *r_it_e << std::endl;
	std::cout <<  "--------------------------------------------------------------\n";
    std::cout << "Copy constructor is creating a copy of the set." << std::endl;
	ft::set<std::string> my_set_copy(my_set);
    std::cout << "Inserting new values to the copy." << std::endl;
	my_set_copy.insert("red");
	my_set_copy.insert("blue");
	my_set_copy.insert("yellow");
	my_set_copy.insert("green");
	print_set(my_set_copy);
    std::cout <<  "--------------------------------------------------------------\n";
    std::cout << "Erasing the first element with an iterator argument." << std::endl;
	my_set.erase(my_set.begin());
	print_set(my_set);
    std::cout << "Find the existing element and return its value." << std::endl;
	ft::set<std::string>::iterator f_it_found = my_set.find("orange");
    std::cout << "The value of the iterator returned by find() is " << *f_it_found << std::endl;
    std::cout << "Erasing the range of elements: the elements removed from the set" << std::endl;
	my_set.erase(f_it_found, my_set.end());
	print_set(my_set);
    std::cout << "Swapping two sets:" << std::endl;
	my_set_copy.swap(my_set);
    std::cout << "my_set:" << std::endl;
	print_set(my_set);
    std::cout << "my_set_copy:" << std::endl;
	print_set(my_set_copy);
    std::cout << "Clearing a copy set won't remove elements from the origin" << std::endl;
	my_set_copy.clear();
	ft::pair<ft::set<std::string>::iterator, ft::set<std::string>::iterator> p = my_set.equal_range("green");
    std::cout << "Equal range return value is" << *(p.first) << std::endl;
    std::cout << "Comparing two sets:" << std::endl;
	if (my_set < my_set_copy)
		std::cout << "my_set is smaller than my_set_copy:" << std::endl;
	else if (my_set > my_set_copy)
		std::cout << "my_set is larger than my_set_copy:" << std::endl;
	else
		std::cout << "my_set equals my_set_copy:" << std::endl;
}
