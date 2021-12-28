#include "map.hpp"
#include <map>
#include <iostream>
#include <string>

// typedef std::map<size_t, size_t> MyMap;

template <class T>
struct PrintMyMap : public std::unary_function<T, void>
{
    std::ostream& os;
    PrintMyMap(std::ostream& strm) : os(strm) {}

    void operator()(const T& elem) const
    {
        os << elem.first << ", " << elem.second << "\n";
    }
};

int main(void )
{
    std::map<int,int> sMap;
    ft::map<int, int> f_map;

    	std::pair<int, int> s_pair(1,100);
		ft::pair<int, int> f_pair(1,100);

        sMap.insert(s_pair);
        f_map.insert(f_pair);

        //
        //     myMap[10]=10;
        //     myMap[4]=30;
        //     myMap[2]=50;
        //     myMap[7]=70;
        // std::for_each(sMap.begin(),
        //           sMap.end(),
        //           PrintMyMap<std::map<size_t, size_t>::value_type>(std::cout));
        // std::for_each(f_map.begin(),
        //           f_map.end(),
        //           PrintMyMap<ft::map<size_t, size_t>::value_type>(std::cout));

        // PrintMyMap<ft::map<size_t, size_t>::value_type> print(std::cout);
        // print.operator()
        ft::map<int, int>::iterator it = f_map.begin();

        std::cout << it->first << it->second;

        return 0;
}