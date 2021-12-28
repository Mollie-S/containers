
#include "catch.hpp"

#include "../map/map.hpp"
#include <map>

// clang++ tests/map_test.cpp -std=c++11 -o testMap && ./testMap

TEST_CASE("Testing map constructors", "[integer keys]")
{
	std::map<int,int> s_map;
	ft::map<int, int> f_map;
	
	SECTION("Inserting a pair")
	{
		std::pair<int, int> s_pair(1,100);
		ft::pair<int, int> f_pair(1,100);
		s_map.insert(s_pair);
		f_map.insert(f_pair);
		std::map<int, int>::iterator s_it = s_map.begin();
		ft::map<int, int>::iterator f_it = f_map.begin();

		REQUIRE(s_it->first == f_it->first);
		REQUIRE(s_it->second == f_it->second);
	}
}
