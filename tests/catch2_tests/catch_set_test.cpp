#include "include/catch.hpp"

#include "set.hpp"
#include <set>

namespace ft {
	template <typename T>
	bool operator==(const ft::set<T>& my_set, const std::set<T>& st_set)
	{
		typename ft::set<T>::const_iterator my_iter_start = my_set.begin();
		typename ft::set<T>::const_iterator my_iter_end = my_set.end();
		typename std::set<T>::const_iterator stl_iter_start = st_set.begin();
		typename std::set<T>::const_iterator stl_iter_end = st_set.end();
		if (my_set.size() != st_set.size())
		{
			return false;
		}
		while (my_iter_start != my_iter_end && stl_iter_start != stl_iter_end)
		{
			if (*stl_iter_start != *stl_iter_start)
			{
				return false;
			}
			my_iter_start++;
			stl_iter_start++;
		}
		return true;
	}

	template <typename T>
	bool operator==(const std::set<T>& st_set, const ft::set<T>& my_set)
	{
		return my_set == st_set;
	}

	template <typename T>
	bool operator!=(const std::set<T>& st_set, const ft::set<T>& my_set)
	{
		return !(st_set == my_set);
	}

	template <typename T>
	bool operator!=(const ft::set<T>& my_set, const std::set<T>& st_set)
	{
		return !(my_set == st_set);
	}
}

TEST_CASE("Constructing and manipulating elements in the set with int keys", "[integer keys]")
{
	std::set<int> st_set;
	ft::set<int> my_set;
	
	SECTION("Insertion")
	{
		st_set.insert(105);
		my_set.insert(105);
		std::set<int>::iterator s_it = st_set.begin();
		ft::set<int>::iterator f_it = my_set.begin();

		CHECK(*s_it == *f_it);
		
		SECTION("set copy constructor: constructs the deep copy of original set, deleting original set won't affect the copy")
		{
			std::set<int> st_set_copy(st_set);
			ft::set<int> my_set_copy(my_set);

			SECTION("Inserting more elements that are smaller and larger than original key. Inserting the same key won't affect the existing key")
			{
				for (int i = 101; i < 120; ++i)
				{
					st_set.insert(i);
					my_set.insert(i);
				}
				CHECK(st_set == my_set);

				ft::set<int>::reverse_iterator my_rev_it = my_set.rbegin();
				std::set<int>::reverse_iterator st_rev_it = st_set.rbegin();

				CHECK(*my_rev_it == *st_rev_it);


				SECTION("Clearing the set: the elements must be destructed")
				{
					my_set.clear();
					st_set.clear();
					CHECK(st_set == my_set);

					SECTION("Insertion - new elements are added to the original set")
					{
						st_set.insert(4);
						my_set.insert(4);
						st_set.insert(40);
						my_set.insert(40);
						st_set.insert(400);
						my_set.insert(400);
						st_set.insert(3);
						my_set.insert(3);
						st_set.insert(30);
						my_set.insert(30);
						st_set.insert(300);
						my_set.insert(300);
						CHECK(st_set == my_set);
					
						SECTION("Insert range: inserting original set into the copy")
						{
							CHECK(my_set_copy.size() == st_set_copy.size()); // checking the size before insertion
							st_set_copy.insert(st_set.begin(), st_set.end());
							my_set_copy.insert(my_set.begin(), my_set.end());
							std::set<int>::iterator s_it = st_set_copy.begin();
							ft::set<int>::iterator f_it = my_set_copy.begin();
							CHECK(*s_it == *f_it);
							ft::set<int>::const_reverse_iterator my_rev_it = my_set_copy.rbegin();
							std::set<int>::const_reverse_iterator st_rev_it = st_set_copy.rbegin();
							CHECK(*st_rev_it == *my_rev_it);
							CHECK(my_set_copy.size() == st_set_copy.size()); // checking the size after insertion
						}
					}
				}
			}

			SECTION("Erase method: erasing a node non existing key does't erase anything")
			{
				st_set_copy.erase(8);
				my_set_copy.erase(8);
				CHECK(st_set_copy == my_set_copy);
			}
			SECTION("Erasing by passing a key will find and destruct the node")
			{
				st_set_copy.erase(101);
				my_set_copy.erase(101);
				CHECK(st_set_copy == my_set_copy);
			}
		}
	}
}

TEST_CASE("Constructing and manipulating elements in the set with string keys", "[string keys]")
{
	std::set<std::string> st_set;
	ft::set<std::string> my_set;

	SECTION("Copy constructor is creating a copy of an empty set")
	{

		std::set<std::string> st_set_to_insert(st_set);
		ft::set<std::string> my_set_to_insert(my_set);
		st_set_to_insert.insert("red");
		my_set_to_insert.insert("red");
		st_set_to_insert.insert("blue");
		my_set_to_insert.insert("blue");
		st_set_to_insert.insert("yellow");
		my_set_to_insert.insert("yellow");
		st_set_to_insert.insert("green");
		my_set_to_insert.insert("green");

		SECTION("Constructing set of strings")
		{
			const char* args[] = {"black", "white", "pink", "purple", "turquoise", "beige", "grey", "maroon", "coral", "orange", "khaki", "fuchsia"};
			size_t length = sizeof(args) / sizeof(args[0]);
			for (int i = 0; i < length; ++i)
			{
				st_set.insert(args[i]);
				my_set.insert(args[i]);
			}
			CHECK(*st_set.begin() == *my_set.begin());
			CHECK(st_set.count("pink") == my_set.count("pink"));
			CHECK(st_set.count("maroon") == my_set.count("maroon"));

			SECTION("Copy constructor")
			{
				std::set<std::string> st_set_copy(st_set);
				ft::set<std::string> my_set_copy(my_set);

				SECTION("Erasing the first element with an iterator argument: the element removed from the set, both sets are equal")
				{
					std::set<std::string>::iterator s_it = st_set.begin();
					ft::set<std::string>::iterator f_it = my_set.begin();
					st_set.erase(s_it);
					my_set.erase(f_it);

					CHECK(st_set == my_set);
				}
				SECTION("Find = the existing element is found")
				{
					std::set<std::string>::iterator s_it_found = st_set.find("orange");
					ft::set<std::string>::iterator f_it_found = my_set.find("orange");
					CHECK(*s_it_found == *f_it_found);

					SECTION("Erasing the range of elements: the elements removed from the set, both sets are equal")
					{
						std::set<std::string>::iterator s_it_end = st_set.end();
						ft::set<std::string>::iterator f_it_end = my_set.end();
						st_set.erase(s_it_found, s_it_end);
						my_set.erase(f_it_found, f_it_end);
						CHECK(st_set == my_set);
					}

					SECTION("Inserting set_copy into the original set will combine elements")
					{
						st_set.insert(st_set_copy.begin(),st_set_copy.end());
						my_set.insert(my_set_copy.begin(), my_set_copy.end());
						CHECK(st_set == my_set);
					}

					SECTION("Swap method swaps pointers to the elements")
					{
						st_set_copy.swap(st_set);
						my_set_copy.swap(my_set);
						CHECK(st_set == my_set);
						CHECK(st_set_copy == my_set_copy);

					}
					SECTION("Clearing one set won't remove elements from the origin")
					{
						st_set_copy.clear();
						my_set_copy.clear();
						CHECK(st_set == my_set);
						CHECK(st_set_copy == my_set_copy);

					}
					SECTION("Reverse iterator")
					{
						std::set<std::string>::reverse_iterator ri1 = st_set.rbegin();
						ft::set<std::string>::reverse_iterator ri2 = my_set.rbegin();
						std::set<std::string>::reverse_iterator ri3 = st_set.rend();
						ft::set<std::string>::reverse_iterator ri4 = my_set.rend();
						ri3--;
						ri4--;
						CHECK(*ri1 == *ri2);
						CHECK(*ri3 == *ri4);
					}
					SECTION("Equal range")
					{
						std::pair<std::set<std::string>::iterator, std::set<std::string>::iterator> p = st_set.equal_range("green");
						ft::pair<ft::set<std::string>::iterator, ft::set<std::string>::iterator> p1 = my_set.equal_range("green");
						CHECK(*(p.first) == *(p1.first));
					}
				}
			}
		}
	}
}

TEST_CASE("const and non const: set instances and iterators comparison and assignment")
{
	ft::set<std::string> my_set;
	my_set.insert("tree");
	ft::set<std::string>::iterator it = my_set.begin();
	ft::set<std::string>::const_iterator it_const;


	SECTION("Assigning non-const iterator to const is possible")
	{
		it_const = it;
		CHECK(it_const == it);
	}
	
	const ft::set<std::string> my_set1;
	ft::set<std::string>::const_iterator itc = my_set1.begin();

	SECTION("Constructing a copy of a const set")
	{
		const ft::set<std::string> my_const_set(my_set);
		CHECK(my_const_set == my_set);

		SECTION("Comparing const and non-const sets is possible")
		{
			CHECK(my_set1 <= my_set);
			CHECK(my_const_set  >= my_set1);
		}

		SECTION("Assigning non-const set to const is possible")
		{
			my_set = my_set1;
			CHECK(my_set == my_set1);
			CHECK(my_const_set != my_set);
		}
	}
}

TEST_CASE("Set instances and iterators values comparison", "[string keys, string values]")
{
	ft::set<std::string> my_set1;
	ft::set<std::string> my_set2(my_set1);
	CHECK(my_set1 == my_set2);

	SECTION("Set comparison operators")
	{
		CHECK(my_set1.begin() != my_set2.begin());
		my_set1.insert("orange"); 
		my_set2.insert("gray");
		CHECK(*(my_set1.begin()) > *(my_set2.begin()));
		my_set1.insert("gray");
		ft::set<std::string>::iterator it1 = my_set1.begin();
		it1++;
		CHECK(*it1 > *(my_set1.begin()));
		CHECK(*(my_set1.begin()) <= *(my_set2.begin()));
		my_set1.insert("yellow");
		my_set1.insert("green");
		CHECK(*(my_set2.rbegin()) < *(my_set1.rbegin()));

		SECTION("set relational operators")
		{
			CHECK(my_set1 != my_set2);
			CHECK(my_set1 > my_set2);
			CHECK(my_set2 < my_set1);
		}
	}
}
