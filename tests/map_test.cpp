
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
		{
			return false;
		}
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

	struct 	 Dummy
	{
		static int counter;
		Dummy() { counter++; }
		~Dummy() { counter--; }
	};

	int Dummy::counter=0;

	class NoDefaultDummy
	{
	private:
		int _num;

	public:
		NoDefaultDummy(int number) : _num(number){}
		~NoDefaultDummy() {}
	};


	class FatDummy
	{
	private:
		char _fat_data[10000000];

	public:
		FatDummy(): _fat_data(){}
		~FatDummy() {}
	};
	
}

TEST_CASE("Testing map constructors", "[integer keys]")
{
	std::map<int,int> stl_map;
	ft::map<int, int> my_map;
	std::map<int,int> stl_empty_copy(stl_map);
	ft::map<int, int> my_empty_copy(my_map);
	
	SECTION("Insertion")
	{
		std::pair<int, int> s_pair(1,100);
		ft::pair<int, int> f_pair(1,100);
		stl_map.insert(s_pair);
		my_map.insert(f_pair);
		std::map<int, int>::iterator s_it = stl_map.begin();
		ft::map<int, int>::iterator f_it = my_map.begin();

		CHECK(s_it->first == f_it->first);
		CHECK(s_it->second == f_it->second);
		
		SECTION("Map copy constructor: constructs the deep copy of original map, deleting original map won't affect the copy")
		{
			std::map<int, int> stl_map_copy(stl_map);
			ft::map<int, int> my_map_copy(my_map);

			SECTION("Inserting more elements to the original map")
			{
				std::pair<int, int> s_pair1(120,1200);
				ft::pair<int, int> f_pair1(120,1200);
				std::pair<int, int> s_pair2(3,300);
				ft::pair<int, int> f_pair2(3,300);
				std::pair<int, int> s_pair3(-3,-300);
				ft::pair<int, int> f_pair3(-3,-300);
				stl_map.insert(s_pair1);
				my_map.insert(f_pair1);
				stl_map.insert(s_pair2);
				my_map.insert(f_pair2);
				stl_map.insert(s_pair3);
				my_map.insert(f_pair3);

				std::map<int, int>::iterator s_it = stl_map.begin();
				ft::map<int, int>::iterator f_it = my_map.begin();
				CHECK(s_it->first == f_it->first);
				CHECK(s_it->second == f_it->second);
				ft::map<int, int>::reverse_iterator my_rev_it = my_map.rbegin();
				std::map<int, int>::reverse_iterator stl_rev_it = stl_map.rbegin();

				CHECK(stl_rev_it->first == my_rev_it->first);
				CHECK(my_map.size() == stl_map.size());
				CHECK(stl_map == my_map);

				SECTION("Clearing the map: the elements must be destructed")
				{
					my_map.clear();
					stl_map.clear();
					CHECK(stl_map == my_map);

					SECTION("Insertion - new elements are added to the original map")
					{
						stl_map.insert(std::make_pair<int, int>(41, 400));
						my_map.insert(ft::make_pair<int, int>(41, 400));
						stl_map.insert(std::make_pair<int, int>(38, 400));
						my_map.insert(ft::make_pair<int, int>(38, 400));
						stl_map.insert(std::make_pair<int, int>(31, 400));
						my_map.insert(ft::make_pair<int, int>(31, 400));
						stl_map.insert(std::make_pair<int, int>(12, 400));
						my_map.insert(ft::make_pair<int, int>(12, 400));
						stl_map.insert(std::make_pair<int, int>(19, 400));
						my_map.insert(ft::make_pair<int, int>(19, 400));
						stl_map.insert(std::make_pair<int, int>(8, 400));
						my_map.insert(ft::make_pair<int, int>(8, 400));
						CHECK(stl_map == my_map);

						SECTION("Insert range: inserting original map into the copy")
						{
							CHECK(my_map_copy.size() == stl_map_copy.size());
							stl_map_copy.insert(stl_map.begin(), stl_map.end());
							my_map_copy.insert(my_map.begin(), my_map.end());

							std::map<int, int>::iterator s_it = stl_map_copy.begin();
							ft::map<int, int>::iterator f_it = my_map_copy.begin();
							CHECK(s_it->first == f_it->first);
							CHECK(s_it->second == f_it->second);
							ft::map<int, int>::const_reverse_iterator my_rev_it = my_map_copy.rbegin();
							std::map<int, int>::const_reverse_iterator stl_rev_it = stl_map_copy.rbegin();
							CHECK(stl_rev_it->first == my_rev_it->first);
							CHECK(my_map_copy.size() == stl_map_copy.size());
						}
					}
				}
			}

			SECTION("Erase method: erasing a node non existing key does't erase anything")
			{
				stl_map_copy.erase(8);
				my_map_copy.erase(8);
				ft::map<int, int>::iterator my_iter_start =my_map_copy.begin();
				ft::map<int, int>::iterator my_iter_end = my_map_copy.end();
				std::map<int, int>::iterator stl_iter_start = stl_map_copy.begin();
				std::map<int,int>::iterator stl_iter_end = stl_map_copy.end();
				while (my_iter_start != my_iter_end && stl_iter_start != stl_iter_end)
				{
					CHECK(stl_iter_start->first == my_iter_start->first);

					my_iter_start++;
					stl_iter_start++;
				}
				CHECK(stl_map_copy == my_map_copy);
			}
			SECTION("Erasing by passing a key will find and destruct the node")
			{
				stl_map_copy.erase(1);
				my_map_copy.erase(1);
				CHECK(stl_map_copy == my_map_copy);
			}
		}
	}
}

TEST_CASE("Range map constructor must create the same amount of the pairs as std map", "[integer keys]")
{
	srand((unsigned) time(0));
	std::vector<std::pair<int, int> > 	s_vect;
	ft::vector<ft::pair<int, int> > 	f_vect;
	for (int index = 10; index < 20; index++) {
		std::pair<int, int> s_pair = std::make_pair(index, index);
		ft::pair<int, int> f_pair = ft::make_pair(index, index);
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

	std::map<int, int> stl_map(s_iter, s_iter_end);
	ft::map<int, int> my_map(f_iter, f_iter_end);
	CHECK(stl_map.size() == my_map.size());

	std::map<int, int>::iterator s_i = stl_map.begin();
	ft::map<int, int>::iterator f_i = my_map.begin();
	CHECK(s_i->first == f_i->first);
	CHECK(stl_map == my_map);
}

TEST_CASE("Map of string - keys ", "[string keys]")
{
	std::map<std::string,std::string> stl_map;
	ft::map<std::string, std::string> my_map;

	SECTION("Copy constructor is creating a copy of an empty map")
	{

		std::map<std::string,std::string> stl_map_to_insert(stl_map);
		ft::map<std::string, std::string> my_map_to_insert(my_map);
		stl_map_to_insert.insert(std::make_pair("tree", "sycamore"));
		my_map_to_insert.insert(ft::make_pair("tree", "sycamore"));
		stl_map_to_insert.insert(std::make_pair("flower", "rose"));
		my_map_to_insert.insert(ft::make_pair("flower", "rose"));
		stl_map_to_insert.insert(std::make_pair("fruit", "banana"));
		my_map_to_insert.insert(ft::make_pair("fruit", "banana"));
		stl_map_to_insert.insert(std::make_pair("vegetable", "cucumber"));
		my_map_to_insert.insert(ft::make_pair("vegetable", "cucumber"));

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
				stl_map.insert(s_pair);
				my_map.insert(f_pair);
			}
			CHECK(stl_map.begin()->first == my_map.begin()->first);
			CHECK(stl_map.count("pea") == my_map.count("pea"));
			CHECK(stl_map.count("is") == my_map.count("is"));
			CHECK(stl_map.count("dress") == my_map.count("dress"));

			SECTION("Erasing an element with an iterator argument removes the element from the map")
			{
				std::map<std::string, std::string>::iterator s_it = stl_map.begin();
				ft::map<std::string, std::string>::iterator f_it = my_map.begin();
				stl_map.erase(s_it);
				my_map.erase(f_it);

				CHECK(stl_map == my_map);
			}
			SECTION("Inserting map_to_insert into the original map will combine elements")
			{
				stl_map.insert(stl_map_to_insert.begin(),stl_map_to_insert.end());
				my_map.insert(my_map_to_insert.begin(), my_map_to_insert.end());
				CHECK(stl_map == my_map);

				
			}

			SECTION("Operator[] with non-existing key adds the element to the map")
			{
				stl_map["berry"] = "blueberry";
				my_map["berry"] = "blueberry";
				CHECK(stl_map == my_map);

				SECTION("Operator[] with existing key will update the value")
				{
					stl_map["berry"] = "strawberry";
					my_map["berry"] = "strawberry";
					CHECK(stl_map == my_map);
				}
			}
			SECTION("Swap method swaps pointers to the elements")
			{
				stl_map_to_insert.swap(stl_map);
				my_map_to_insert.swap(my_map);
				CHECK(stl_map == my_map);
				CHECK(stl_map_to_insert == my_map_to_insert);

			}
		}
	}
}

TEST_CASE("const and non const ")
{
	ft::map<std::string, std::string> my_map;
	my_map.insert(ft::make_pair("tree", "sycamore"));
	ft::map<std::string, std::string>::iterator it = my_map.begin();
	ft::map<std::string, std::string>::const_iterator it_const;


	SECTION("Assigning non-const iterator to const is possible")
	{
		it_const = it;
		CHECK(it_const == it);
	}
	
	const ft::map<std::string, std::string> my_map1;
	ft::map<std::string, std::string>::const_iterator itc = my_map1.begin();

	SECTION("Constructing a copy of a const map")
	{
		const ft::map<std::string, std::string> my_const_map(my_map);
		CHECK(my_const_map == my_map);

		SECTION("Comparing const and non-const maps is possible")
		{
			CHECK(my_map1 <= my_map);
			CHECK(my_const_map  >= my_map1);
		}

		SECTION("Assigning non-const map to const is possible")
		{
			my_map = my_map1;
			CHECK(my_map == my_map1);
			CHECK(my_const_map != my_map);
		}
	}
}

TEST_CASE("Comparison", "[string keys, string values]")
{
	ft::map<std::string, std::string > my_map1;
	ft::map<std::string, std::string > my_map2(my_map1);
	CHECK(my_map1 == my_map2);

	SECTION("Iterator comparison operators")
	{
		CHECK(my_map1.begin() != my_map2.begin());
		my_map1.insert(ft::make_pair("tree", "sycamore"));
		my_map2.insert(ft::make_pair("flower", "rose"));
		CHECK(my_map1.begin()->first > my_map2.begin()->first);
		my_map1.insert(ft::make_pair("flower", "rose"));
		CHECK(my_map1.begin()->first <= my_map2.begin()->first);
		my_map1.insert(ft::make_pair("fruit", "banana"));
		my_map1.insert(ft::make_pair("vegetable", "cucumber"));
		CHECK(my_map2.rbegin()->first < my_map1.rbegin()->first);

		SECTION("Map relational operators")
		{
			CHECK(my_map1 != my_map2);
			CHECK(my_map1 > my_map2);
			CHECK(my_map2 < my_map1);
		}
	}
}


TEST_CASE("Testing the sentinel node", "[sentinel]")
{
	SECTION("Creating the map from a class having no default constructor - should cause no problem")
	{
		ft::map<int, ft::NoDefaultDummy> my_map;
		std::map<int, ft::NoDefaultDummy> stl_map;

		ft::NoDefaultDummy dummy(10);
		my_map.insert(ft::make_pair(1, dummy));
		stl_map.insert(std::make_pair(1, dummy));

		CHECK(stl_map == my_map);
	}

	SECTION("Calculating number of Dummy instances - ")
	{
		ft::map<int, ft::Dummy> my_map;
		std::map<int, ft::Dummy> stl_map;

		CHECK(ft::Dummy::counter == 0);
	}

	SECTION("Creating the map from a class with big data - no stack overflow ")
	{
		ft::map<int, ft::FatDummy> my_map;
		std::map<int, ft::FatDummy> stl_map;

		CHECK(stl_map == my_map);
	}
}
