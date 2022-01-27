#include "include/tests.hpp"

template <typename K, typename T>
void print_map(const ft::map<K, T>& m)
{
    typename ft::map<K, T>::const_iterator f_it = m.begin();
    typename ft::map<K, T>::const_iterator itEnd = m.end();
    std::cout << "The map looks like this:\n";
    if (m.empty())
    {
        std::cout << "The map is empty\n";
    }
    for (typename ft::map<K, T>::const_iterator i = f_it; i != itEnd; ++i)
    {
        std::cout  << "Key: " << i->first << std::endl;
        std::cout  << "Value: " << i->second << std::endl;
    }
    std::cout  << "Size: " << m.size() << std::endl;
    std::cout <<"--------------------------------------------------"<<  std::endl;
}

template <typename K, typename T>
void is_found_output_print(typename ft::map<K,T>::iterator& it, typename ft::map<K,T>::iterator& end)
{
    if (it != end)
        std::cout << "The element is found. Its value is: "<< it->second << std::endl;
    else
        std::cout << "The element is not found." << std::endl;
}

ft::map<std::string, std::string> create_map_of_strings()
{
    ft::pair<std::string, std::string> my_p1 = ft::make_pair("tree", "sycamore");
    ft::pair<std::string, std::string> my_p2 = ft::make_pair("flower", "rose");
    ft::pair<std::string, std::string> my_p3 = ft::make_pair("fruit", "banana");
    ft::pair<std::string, std::string> my_p4 = ft::make_pair("vegetable", "cucumber");

    ft::map<std::string, std::string> my_m;
    my_m.insert(my_p1);
    my_m.insert(my_p2);
    my_m.insert(my_p3);
    my_m.insert(my_p4);
    return my_m;
}

ft::map<int, int> create_large_map_of_ints()
{
    ft::map<int, int> my_m;
    for (int i = 0; i < INT_MAX/100000; ++i)
    {
        my_m.insert(ft::make_pair(i,i));
    }
    return my_m;
}

void map_test()
{
    const char* args1[] = {"drill", "ice", "hat", "arm", "is", "the", "cheese", "root", "pea","more"};
    const char* args2[] = {"01", "02", "03", "04", "05", "06", "07", "08", "09","10"};
    size_t length1 = sizeof(args1) / sizeof(args1[0]);
    size_t length2 = sizeof(args2) / sizeof(args2[0]);
 
    std::cout << "\n\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "|                MAP                    |\n";
    std::cout << "-----------------------------------------\n";
    std::cout << "Creating an empty map." << std::endl;
	ft::map<std::string, std::string> m;
    print_map(m);
    std::cout << "Inserting one new value." << std::endl;
    m.insert(ft::make_pair("color", "green"));
    print_map(m);
    std::cout << "Inserting more new values." << std::endl;
    for (size_t i = 0; i < length1 && i < length2; ++i)
    {
        ft::pair<std::string, std::string> f_pair(args1[i], args2[i]);
		m.insert(f_pair);
    }
    print_map(m);
    std::cout << "Creating another map of strings." << std::endl;
    ft::map<std::string, std::string> my_map = create_map_of_strings();
    print_map(my_map);

    std::cout << "Element access check:" << std::endl;
    std::cout << "Accessing the element with the help of the operator[]: " << my_map["flower"] << std::endl;

    std::cout <<  "--------------------------------------------------------------\n";
    std::cout << "Iterators check:" << std::endl;
    std::cout << "The element accessed by calling begin() has the key: " <<  my_map.begin()->first << std::endl;
    ft::map<std::string, std::string>::iterator l = my_map.end();
    l--;
    std::cout << "The element preceeding the iterator end() has the key: " << l->first << std::endl;
    ft::map<std::string, std::string>::reverse_iterator rl = my_map.rend();
    rl--;
    std::cout << "The dereferenced reverse iterator following the rend()(should be the first element) has the key: " << rl->first << std::endl;
    std::cout << "The dereferenced reverse iterator accessed by rbegin()(should be the last element) has the key: " << my_map.rbegin()->first << std::endl;

    std::cout << "Inserting another map into the original one." << std::endl;
	m.insert(my_map.begin(), my_map.end());
    print_map(m);

    std::cout << "Copy constructing." << std::endl;
	ft::map<std::string, std::string> copy(m);

    std::cout << "Erasing an element from the original map." << std::endl;
    m.erase("root");
    print_map(m);

    std::cout << "Finding an element by its key." << std::endl;
    ft::map<std::string, std::string>::iterator it = m.find("pea");
    // is_found_output_print(it, m.end());
    if (it != m.end())
        std::cout << "The element is found. Its value is: "<< it->second << std::endl;
    else
        std::cout << "The element is not found." << std::endl;

	std::cout <<  "--------------------------------------------------------------\n";
    std::cout << "Erasing a  range  of elements from the original map." << std::endl;
    m.erase(it, m.end());
    print_map(m);

    std::cout << "Clearing the original map." << std::endl;
    m.clear();
    print_map(m);

    std::cout << "Swapping the original map and the copy and printing the original." << std::endl;
    m.swap(copy);
    print_map(m);

    std::cout << "Finding an element with equal_range()." << std::endl;
    ft::pair<ft::map<std::string, std::string>::iterator, ft::map<std::string, std::string>::iterator> p = m.equal_range("fruit");
    if (p.first != m.end())
        std::cout << "The element is found. Its value is: "<< p.first->second << std::endl;
    else
        std::cout << "The element is not found." << std::endl;
	std::cout <<  "--------------------------------------------------------------\n";

    {
        std::cout << "Creating a large map of ints." << std::endl;
        ft::map<int, int> m_int = create_large_map_of_ints();
        std::cout << "The map size is: "<< m_int.size()<< std::endl;

        std::cout << "Searching the map of ints." << std::endl;
        ft::map<int, int>::iterator it = m_int.find(20000);
        if (it != m_int.end())
            std::cout << "The element is found. Its value is: "<< it->second << std::endl;
        else
            std::cout << "The element is not found." << std::endl;
        std::cout <<  "--------------------------------------------------------------\n";
        std::cout << "The lower bound key of the key 300 is " << m_int.lower_bound(300)->first << std::endl;
        std::cout << "The upper bound key of the key 300 is " << m_int.upper_bound(300)->first << std::endl;
    }
}
