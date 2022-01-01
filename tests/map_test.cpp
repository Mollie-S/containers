
#include "catch.hpp"

#include "../map/map.hpp"
#include <map>
#include "../vector/vector.hpp"
#include <vector>

// clang++ tests/map_test.cpp -std=c++11 -o testMap && ./testMap

TEST_CASE("Testing map constructors", "[integer keys]")
{
	std::map<int,int> s_map;
	ft::map<int, int> f_map;
	
	SECTION("Insertion")
	{
		std::pair<int, int> s_pair(1,100);
		ft::pair<int, int> f_pair(1,100);
		s_map.insert(s_pair);
		f_map.insert(f_pair);
		std::map<int, int>::iterator s_it = s_map.begin();
		ft::map<int, int>::iterator f_it = f_map.begin();

		CHECK(s_it->first == f_it->first);
		CHECK(s_it->second == f_it->second);
		

		SECTION("Inserting more elements")
		{
			std::pair<int, int> s_pair1(120,1200);
			ft::pair<int, int> f_pair1(120,1200);
			std::pair<int, int> s_pair2(3,300);
			ft::pair<int, int> f_pair2(3,300);
			std::pair<int, int> s_pair3(-3,-300);
			ft::pair<int, int> f_pair3(-3,-300);
			s_map.insert(s_pair1);
			f_map.insert(f_pair1);
			s_map.insert(s_pair2);
			f_map.insert(f_pair2);
			s_map.insert(s_pair3);
			f_map.insert(f_pair3);

			std::map<int, int>::iterator s_it = s_map.begin();
			ft::map<int, int>::iterator f_it = f_map.begin();
			CHECK(s_it->first == f_it->first);
			CHECK(s_it->second == f_it->second);
			
		}
	}
}

TEST_CASE("Range map constructor must create the same amount of the pairs as std map", "[integer keys]")
{
	srand((unsigned) time(0));
	std::vector<std::pair<int, int> > 	s_vect;
	ft::vector<ft::pair<int, int> > 	f_vect;
	int randomKey;
	int randomValue;
	for (int index = 0; index < 100; index++) {
    	randomKey = (rand() % 350) + 1;
    	randomValue = (rand() % 1000) + 1;
		std::pair<int, int> s_pair = std::make_pair(randomKey, randomValue);
		ft::pair<int, int> f_pair = ft::make_pair(randomKey, randomValue);
		s_vect.push_back(s_pair);
		f_vect.push_back(f_pair);
	}

	std::vector<std::pair<int, int> >::iterator s_iter = s_vect.begin();
	ft::vector<ft::pair<int, int> >::iterator f_iter = f_vect.begin();
	std::vector<std::pair<int, int> >::iterator s_iter_end = s_vect.end();
	ft::vector<ft::pair<int, int> >::iterator f_iter_end = f_vect.end();
	int key = s_iter->first;
	CHECK(s_iter->first == f_iter->first);
	CHECK(s_vect.size() == f_vect.size());

	std::map<int, int> s_map(s_iter, s_iter_end);
	ft::map<int, int> f_map(f_iter, f_iter_end);
	CHECK(s_map.size() == f_map.size());

	std::map<int, int>::iterator s_i = s_map.begin();
	ft::map<int, int>::iterator f_i = f_map.begin();
	CHECK(s_i->first == f_i->first);

}

TEST_CASE("Map of string - keys ", "[string keys]")
{
	std::map<std::string,std::string> s_map;
	ft::map<std::string, std::string> f_map;

	SECTION("Constructing map of strings")
	{
		const char* args1[] = {"drill", "ice", "hat", "arm", "is", "the", "cheese", "root", "pea","more"};
		const char* args2[] = {"01", "02", "03", "04", "05", "06", "07", "08", "09","10"};
		size_t length1 = sizeof(args1) / sizeof(args1[0]);
		size_t length2 = sizeof(args2) / sizeof(args2[0]);
		for (int i = 0; i < length1 && i < length2; ++i)
		{
			std::pair<std::string, std::string> s_pair(args1[i], args2[i]);
			ft::pair<std::string, std::string> f_pair(args1[i], args2[i]);
			s_map.insert(s_pair);
			f_map.insert(f_pair);
		}
		CHECK(s_map.count("pea") == f_map.count("pea"));
		CHECK(s_map.count("is") == f_map.count("is"));
		CHECK(s_map.count("dress") == f_map.count("dress"));
	}
}