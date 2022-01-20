#ifndef TESTS_HPP
#define TESTS_HPP

#include <string>
#include <iostream>
#include <deque>
#ifdef STD //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "../map/map.hpp"
	#include "../stack/stack.hpp"
	#include "../vector/vector.hpp"
	#include "../set/set.hpp"
#endif

#include <stdlib.h>
#include <limits.h>

void vector_test();
void map_test();

#endif
