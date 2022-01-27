#ifndef TESTS_HPP
#define TESTS_HPP

#include <string>
#include <iostream>
#include <deque>
#ifdef STD //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	#include <set>
	namespace ft = std;
#else
	#include "map.hpp"
	#include "stack.hpp"
	#include "vector.hpp"
	#include "set.hpp"
#endif

#include <stdlib.h>
#include <limits.h>

void vector_test();
void stack_test();
void map_test();
void set_test();

#endif
