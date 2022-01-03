
#include "catch.hpp"

#include "../map/map.hpp"
#include <map>
#include "../vector/vector.hpp"
#include <vector>

// clang++ tests/map_test.cpp -std=c++11 -o testMap && ./testMap

namespace ft {
	template <typename T1,typename T2>
	bool operator==(const ft::map<T1,T2>& my_map, const std::map<T1,T2>& stl_map)
	{
		typename ft::map<T1, T2>::const_iterator my_iter_start = my_map.begin();
		typename ft::map<T1, T2>::const_iterator my_iter_end = my_map.end();
		typename std::map<T1, T2>::const_iterator stl_iter_start = stl_map.begin();
		typename std::map<T1, T2>::const_iterator stl_iter_end = stl_map.end();
		if (my_map.size() != stl_map.size())
			return false;
		while (my_iter_start != my_iter_end && stl_iter_start != stl_iter_end)
		{
			if (my_iter_start->first != stl_iter_start->first)
			{
				return false;
			}
			my_iter_start++;
			stl_iter_start++;
		}
		return true;
	}

	template <typename T1,typename T2>
	bool operator==(const std::map<T1,T2>& stl_map, const ft::map<T1,T2>& my_map)
	{
		return my_map == stl_map;
	}

	template <typename T1,typename T2>
	bool operator!=(const std::map<T1,T2>& stl_map, const ft::map<T1,T2>& my_map)
	{
		return !(stl_map == my_map);
	}

	template <typename T1,typename T2>
	bool operator!=(const ft::map<T1,T2>& my_map, const std::map<T1,T2>& stl_map)
	{
		return !(my_map == stl_map);
	}
}

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
		
		SECTION("Map copy constructor")
		{
			std::map<int, int> s_map_copy(s_map);
			ft::map<int, int> f_map_copy(f_map);
			SECTION("Inserting more elements to the original map")
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
				CHECK(s_map == f_map);
				
				SECTION("Clearing the map")
				{
					f_map.clear();
					s_map.clear();
					CHECK(s_map == f_map);

					SECTION("Insertion")
					{
						s_map.insert(std::make_pair<int, int>(41, 400));
						f_map.insert(ft::make_pair<int, int>(41, 400));
						s_map.insert(std::make_pair<int, int>(38, 400));
						f_map.insert(ft::make_pair<int, int>(38, 400));
						s_map.insert(std::make_pair<int, int>(31, 400));
						f_map.insert(ft::make_pair<int, int>(31, 400));
						s_map.insert(std::make_pair<int, int>(12, 400));
						f_map.insert(ft::make_pair<int, int>(12, 400));
						s_map.insert(std::make_pair<int, int>(19, 400));
						f_map.insert(ft::make_pair<int, int>(19, 400));
						s_map.insert(std::make_pair<int, int>(8, 400));
						f_map.insert(ft::make_pair<int, int>(8, 400));
						CHECK(s_map == f_map);

					}
				}
			}
			SECTION("Erase method")
			{
				s_map_copy.erase(8);
				f_map_copy.erase(8);
				CHECK(s_map_copy == f_map_copy);
				s_map_copy.erase(1);
				f_map_copy.erase(1);
				CHECK(s_map_copy == f_map_copy);

			}
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
	CHECK(s_map == f_map);


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
		CHECK(s_map.begin()->first == f_map.begin()->first);
		CHECK(s_map.count("pea") == f_map.count("pea"));
		CHECK(s_map.count("is") == f_map.count("is"));
		CHECK(s_map.count("dress") == f_map.count("dress"));

		SECTION("Erasing an element with an iterator argument")
		{
			std::map<std::string, std::string>::iterator s_it = s_map.begin();
			ft::map<std::string, std::string>::iterator f_it = f_map.begin();
			s_map.erase(s_it);
			f_map.erase(f_it);

			CHECK(s_map == f_map);

		}
	}
}