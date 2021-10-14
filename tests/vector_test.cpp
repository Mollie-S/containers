#define CATCH_CONFIG_MAIN 
#include "catch.hpp"

#include "../vector/vector.hpp"
#include <vector>


TEST_CASE("Creating an integers container", "[integers]") // [] - is a tag used to select which tests to run
{
    SECTION("Creating an empty container with default constructor")
    {
        ft::vector<int> ftVectorInts;
        std::vector<int> stdVectorInts;
        REQUIRE(ftVectorInts.empty() == stdVectorInts.empty());
        REQUIRE(ftVectorInts.size() == stdVectorInts.size());
        REQUIRE(ftVectorInts.capacity() == stdVectorInts.capacity());
    }

    SECTION("Creating an empty container with fill constructor")
    {
        ft::vector<int> ftVectorInts(5, 10);
        std::vector<int> stdVectorInts(5, 10);
        REQUIRE(ftVectorInts.empty() == stdVectorInts.empty());
        REQUIRE(ftVectorInts.size() == stdVectorInts.size());
        REQUIRE(ftVectorInts.max_size() == stdVectorInts.max_size());
        REQUIRE(ftVectorInts.capacity() == stdVectorInts.capacity());
        REQUIRE(ftVectorInts.size() == 5);
    }
}
TEST_CASE("Testing reserve method", "[integers]") // do it for ft_container!!!!
{
    std::vector<int> stdVectorInts(5, 10);
    std::vector<int>::iterator it;
    std::vector<int>::iterator it1;
    it =  stdVectorInts.begin();
    stdVectorInts.reserve(100);
    it1 =  stdVectorInts.begin();
    REQUIRE(it != it1);
}
