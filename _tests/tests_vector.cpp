#include "tests.hpp"

template <typename T>
void print_vector(const ft::vector<T>& vec)
{
	std::cout << "Our current vector looks like this:" << std::endl;
	typename ft::vector<T>::const_iterator it_start = vec.begin();
	typename ft::vector<T>::const_iterator it_end = vec.end();
	if (vec.empty())
	{
		std::cout << "Opps, the vector is empty. " << std::endl;
	}
	while (it_start != it_end)
	{
		std::cout << *it_start << std::endl;
		it_start++;
	}
	std::cout << "Size is: " << vec.size() << std::endl;
	std::cout <<  "--------------------------------------------------------------\n";
}

void vector_test()
{
	int int_arr[] = { 1, 2, 3, 4, 5, 6, 7, 100, 101, 102, 103, 104, 12, 13, 14, 89};
	size_t arr_size = sizeof(int_arr)/ sizeof(int_arr[0]);
	int int_arr1[] = { -200,-201, -202, -203, -204, -205, -206, -207, -208};
	size_t arr_size1 = sizeof(int_arr1)/ sizeof(int_arr1[0]);

		std::cout << "-----------------------------------------\n";
		std::cout << "|                VECTOR                 |\n";
		std::cout << "-----------------------------------------\n";
		std::cout << "Creating a vector of  integers." << std::endl;
		ft::vector<int> vec;
		std::cout << "Inserting one value." << std::endl;
		vec.insert(vec.begin(), 30);
		print_vector(vec);

		std::cout << "Filling the vector with values(inserting them at the beginning of the vector)" << std::endl;
		vec.insert(vec.begin(), 5, -1000);
		print_vector(vec);

		std::cout << "Inserting a range of values at the end." << std::endl;
		vec.insert(vec.end(), int_arr, int_arr + arr_size);
		print_vector(vec);

		std::cout << "Assign ints range: previous values are destroyed, size changed" << std::endl;
		vec.assign(int_arr1, int_arr1 + arr_size1);
		print_vector(vec);
		std::cout << "Element access check:" << std::endl;
		std::cout << "The element at position 4 is: " << vec.at(4) << std::endl;
		std::cout << "Same position 4, accessing the element with the help of the operator[]: " << vec[4] << std::endl;
		std::cout << "First element is: " << vec.front() << std::endl;
		std::cout << "Last element is: " << vec.back() << std::endl;
		std::cout <<  "--------------------------------------------------------------\n";
		std::cout << "Iterators check:" << std::endl;
		std::cout << "The element accessed by calling begin() is: " <<  *vec.begin() << std::endl;
		std::cout << "The element accessed by iterator end() - 1 (the last element of the vector) is: " << *(vec.end() - 1) << std::endl;
		std::cout << "The dereferenced reverse iterator accessed by rbegin() - 1(should be the last element) is: " << *(vec.rbegin()) << std::endl;
		std::cout << "The dereferenced reverse iterator accessed by rend() - 1(should be the first element) is: " << *(vec.rend() - 1) << std::endl;


		std::cout << "Constructing a copy of the original vector" << std::endl;
		ft::vector<int> copy(vec);
		std::cout << "Printing the copy:" << std::endl;
		print_vector(copy);
		std::cout << "Clearing the original vector" << std::endl;
		vec.clear();
		print_vector(vec);
		std::cout << "The copy is unchanged:" << std::endl;
		print_vector(copy);
		std::cout << "Assigning copy to the original vector (operator=):" << std::endl;
		vec = copy;
		print_vector(vec);

		std::cout << "Pushing back a new value to the original and printing it" << std::endl;
		vec.push_back(300000000);
		vec.push_back(-300000000);
		print_vector(vec);

		std::cout << "Erasing a value at the position 2. (-202 must disappear)" << std::endl;
		vec.erase(vec.begin() + 2);
		print_vector(vec);

		std::cout << "Resizing the original to contain 30 elements" << std::endl;
		vec.resize(30);
		print_vector(vec);

		std::cout << "Resizing the copy to contain 2 elements" << std::endl;
		copy.resize(2);
		print_vector(copy);

		std::cout << "Pushing many elements... Patience, it might take some time." << std::endl;
		for (int i = 0; i < INT_MAX; ++i)
		{
			copy.push_back(i);
		}
		std::cout << "The last element is: " << copy.back() << std::endl;
		

}
