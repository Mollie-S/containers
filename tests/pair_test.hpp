#define CATCH_CONFIG_MAIN 
#include "catch.hpp"

#include "../utility/pair.hpp"
#include <utility>

// clang++ tests/map_test.cpp -std=c++11 -o testPair && ./testPair

TEST_CASE("Pair must be constructed", "[integer keys]")
{
    ft::pair<int,int> ft_pair1;
    ft::pair<int,int> ft_pair2(1,2);
    ft::pair<int,int> ft_pair3(ft_pair2);

    std::pair<int,int> std_pair1;
    std::pair<int,int> std_pair2(1,2);
    std::pair<int,int> std_pair3(std_pair2);

    ft::pair<int,int> ft_pair_from_make = ft::make_pair(5,6);
    std::pair<int,int> std_pair_from_make = std::make_pair(5,6);
}
