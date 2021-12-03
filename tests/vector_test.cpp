#define CATCH_CONFIG_MAIN 
#include "catch.hpp"

#include "../vector/vector.hpp"
#include <vector>

// add to the command line:
// -std=c++11

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

    SECTION("Creating a container with fill constructor")
    {
        ft::vector<int> ftVectorInts(5, 10);
        std::vector<int> stdVectorInts(5, 10);
        REQUIRE(ftVectorInts.empty() == stdVectorInts.empty());
        REQUIRE(ftVectorInts.size() == stdVectorInts.size());
        REQUIRE(ftVectorInts.max_size() == stdVectorInts.max_size());
        REQUIRE(ftVectorInts.capacity() == stdVectorInts.capacity());
        REQUIRE(ftVectorInts.size() == 5);
    }

    SECTION("Creating a container with the range constructor")
    {
        int intArray[] = { 1, 2, 9, 10, 11, 12, 13, 14};
        size_t arraySize = sizeof(intArray)/ sizeof(intArray[0]);
        ft::vector<int> ftVectorInts(intArray, intArray + arraySize);
        std::vector<int> stdVectorInts(intArray, intArray + arraySize);
        REQUIRE(ftVectorInts.empty() == stdVectorInts.empty());
        REQUIRE(ftVectorInts.size() == stdVectorInts.size());
        REQUIRE(ftVectorInts.max_size() == stdVectorInts.max_size());
        REQUIRE(ftVectorInts.capacity() == stdVectorInts.capacity());
    }
}
TEST_CASE("Iterators test", "[integers]")
{

        SECTION("Iterator begin")
    {
        int intArray[] = { 100, 2, 9, 10, 11, 12, 13, 14, 15, 19, 20, 21, 22, 23, 24,25, 28, 29, 30};
        size_t arraySize = sizeof(intArray)/ sizeof(intArray[0]);
        ft::vector<int> ftVectorInts(intArray, intArray + arraySize);
        std::vector<int> stdVectorInts(intArray, intArray + arraySize);
        ft::vector<int>::iterator ftIt = ftVectorInts.begin();
        std::vector<int>::iterator stdIt  = stdVectorInts.begin();
        REQUIRE(*ftIt == *stdIt);
    }
        SECTION("Iterator end()")
    {
        int intArray[] = { 100, 2, 9, 10, 11, 12, 13, 14, 15, 19, 20, 21, 22, 23, 24,25, 28, 29, 30};
        size_t arraySize = sizeof(intArray)/ sizeof(intArray[0]);
        ft::vector<int> ftVectorInts(intArray, intArray + arraySize);
        std::vector<int> stdVectorInts(intArray, intArray + arraySize);
        ft::vector<int>::iterator ftIt = ftVectorInts.end();
        std::vector<int>::iterator stdIt  = stdVectorInts.end();
        REQUIRE(*(ftIt - 1) == *(stdIt - 1));
    }
}


TEST_CASE("Testing reserve method", "[integers]")
{
    ft::vector<int> ftVectorInts(5, 10);
    size_t capacity_1 = ftVectorInts.capacity();
    ftVectorInts.reserve(100);
    size_t capacity_2 = ftVectorInts.capacity();
    REQUIRE(capacity_1 != capacity_2 );
    // std::vector<int> stdVectorInts(5, 10);
    // std::vector<int>::iterator it;
    // std::vector<int>::iterator it1;
    // it =  stdVectorInts.begin();
    // stdVectorInts.reserve(100);
    // it1 =  stdVectorInts.begin();
    // REQUIRE(it != it1);
}
