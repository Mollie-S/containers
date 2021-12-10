#define CATCH_CONFIG_MAIN 
#include "catch.hpp"

#include "../vector/vector.hpp"
#include <vector>

// add to the command line:
// -std=c++11

// (or just copy-paste:
// clang++ tests/vector_test.cpp -std=c++11 -o testVector && ./testVector

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


TEST_CASE("Reserve() method", "[integers]")
{
    SECTION("Checking capacity after reserve")
    {
        ft::vector<int> ftVectorInts(5, 10);
        std::vector<int> stdVectorInts(5,10);
        size_t capacity_1 = ftVectorInts.capacity();
        ftVectorInts.reserve(100);
        stdVectorInts.reserve(100);
        size_t capacity_2 = ftVectorInts.capacity();
        REQUIRE(capacity_1 != capacity_2);
        REQUIRE(ftVectorInts.capacity() == stdVectorInts.capacity());
    
    }
}

TEST_CASE("Testing erase method", "[integers]")
{
    SECTION("Erasing the last element")
    {
        int intArray[] = { 20000, 2, 9, 10, 11, 12, 13, 14, 89};
        size_t arraySize = sizeof(intArray)/ sizeof(intArray[0]);
        ft::vector<int> ftVectorInts(intArray, intArray + arraySize);
        std::vector<int> stdVectorInts(intArray, intArray + arraySize);
        ft::vector<int>::iterator ftItEnd = ftVectorInts.end();
        std::vector<int>::iterator stdItEnd  = stdVectorInts.end();
        ftVectorInts.erase(ftItEnd - 1);
        stdVectorInts.erase(stdItEnd - 1);
        REQUIRE(*(ftVectorInts.end() - 1) == *(stdVectorInts.end() - 1));
    }
    SECTION("Erasing the first element")
    {
        int intArray[] = { 20000, 2, 9, 10, 11, 12, 13, 14, 89};
        size_t arraySize = sizeof(intArray)/ sizeof(intArray[0]);
        ft::vector<int> ftVectorInts(intArray, intArray + arraySize);
        std::vector<int> stdVectorInts(intArray, intArray + arraySize);
        ft::vector<int>::iterator ftIt = ftVectorInts.begin();
        std::vector<int>::iterator stdIt  = stdVectorInts.begin();
        ftVectorInts.erase(ftIt);
        stdVectorInts.erase(stdIt);
        REQUIRE(*(ftVectorInts.begin()) == *(stdVectorInts.begin()));
        REQUIRE(*(ftVectorInts.end() - 1) == *(stdVectorInts.end() - 1));
    }
    SECTION("Erasing the range")
    {
        int intArray[] = { 20000, 2, 9, 10, 11, 0, 0, 0, 0, 0, 12, 13, 14, 89};
        size_t arraySize = sizeof(intArray)/ sizeof(intArray[0]);
        ft::vector<int> ftVectorInts(intArray, intArray + arraySize);
        std::vector<int> stdVectorInts(intArray, intArray + arraySize);
        ft::vector<int>::iterator ftIt = ftVectorInts.begin();
        std::vector<int>::iterator stdIt  = stdVectorInts.begin();
        ft::vector<int>::iterator ftReturnedIt =  ftVectorInts.erase(ftIt + 5, ftIt + 10);
        std::vector<int>::iterator stdReturnedIt  = stdVectorInts.erase(stdIt + 5, stdIt + 10);
        REQUIRE(ftVectorInts.size() == stdVectorInts.size());
        // REQUIRE(ftVectorInts.capacity() == stdVectorInts.capacity()); // // uncomment when iterator traits ready
        REQUIRE(*(ftVectorInts.begin() + 5) == *(stdVectorInts.begin() + 5));
        REQUIRE(*(ftVectorInts.end() - 1) == *(stdVectorInts.end() - 1));
        REQUIRE(*(ftReturnedIt) == *(stdReturnedIt));
    }
}
TEST_CASE("Resize method", "[integers]")
{
    SECTION("Resize to smaller size")
    {
        int intArray[] = { 20000, 2, 9, 10, 11, 12, 13, 14, 89};
        size_t arraySize = sizeof(intArray)/ sizeof(intArray[0]);
        ft::vector<int> ftVectorInts(intArray, intArray + arraySize);
        std::vector<int> stdVectorInts(intArray, intArray + arraySize);
        ft::vector<int>::iterator ftItEnd = ftVectorInts.end();
        std::vector<int>::iterator stdItEnd  = stdVectorInts.end();
        ftVectorInts.resize(3);
        stdVectorInts.resize(3);
        REQUIRE(ftVectorInts.size() == stdVectorInts.size());
        // REQUIRE(ftVectorInts.capacity() == stdVectorInts.capacity()); // uncomment when iterator traits ready
        REQUIRE(*(ftVectorInts.begin()) == *(stdVectorInts.begin()));
        REQUIRE(*(ftVectorInts.end() - 1) == *(stdVectorInts.end() - 1));
    }
    SECTION("Resize to larger size")
    {
        int intArray[] = { 20000, 2, 9, 10, 11, 12, 13, 14, 89};
        size_t arraySize = sizeof(intArray)/ sizeof(intArray[0]);
        ft::vector<int> ftVectorInts(intArray, intArray + arraySize);
        std::vector<int> stdVectorInts(intArray, intArray + arraySize);
        ftVectorInts.resize(30);
        stdVectorInts.resize(30);
        REQUIRE(ftVectorInts.size() == stdVectorInts.size());
        REQUIRE(ftVectorInts.capacity() == stdVectorInts.capacity());
        REQUIRE(*(ftVectorInts.begin()) == *(stdVectorInts.begin()));
        REQUIRE(*(ftVectorInts.end() - 1) == *(stdVectorInts.end() - 1));
    }
    SECTION("Resize to 0")
    {
        int intArray[] = { 20000, 2, 9, 10, 11, 12, 13, 14, 89};
        size_t arraySize = sizeof(intArray)/ sizeof(intArray[0]);
        ft::vector<int> ftVectorInts(intArray, intArray + arraySize);
        std::vector<int> stdVectorInts(intArray, intArray + arraySize);
        ftVectorInts.resize(0);
        stdVectorInts.resize(0);
        REQUIRE(ftVectorInts.size() == stdVectorInts.size());
        // REQUIRE(ftVectorInts.capacity() == stdVectorInts.capacity());// uncomment when iterator traits ready
        // no iterators check as there are no elements
    }
}
TEST_CASE("Swap() method", "[integers]")
{
    SECTION("ft::swap")
    {
        int intArray[] = { 20000, 2, 9, 10, 11, 12, 13, 14, 89};
        size_t arraySize = sizeof(intArray)/ sizeof(intArray[0]);
        ft::vector<int> ftVectorInts(intArray, intArray + arraySize);
        std::vector<int> stdVectorInts(intArray, intArray + arraySize);

        ft::vector<int> ftVectorInts1(5, 10);
        std::vector<int> stdVectorInts1(5,10);

        ft::swap(ftVectorInts,ftVectorInts1);
        std::swap(stdVectorInts,stdVectorInts1);
        ft::vector<int>::iterator ftIt = ftVectorInts.begin();
        std::vector<int>::iterator stdIt = stdVectorInts.begin();
        REQUIRE(*(ftIt) == *(stdIt));

    }
    SECTION("ft::vector:;swap")
    {
        int intArray[] = { 20000, 2, 9, 10, 11, 12, 13, 14, 89};
        size_t arraySize = sizeof(intArray)/ sizeof(intArray[0]);
        ft::vector<int> ftVectorInts(intArray, intArray + arraySize);
        std::vector<int> stdVectorInts(intArray, intArray + arraySize);

        ft::vector<int> ftVectorInts1(5, 10);
        std::vector<int> stdVectorInts1(5,10);

        ftVectorInts.swap(ftVectorInts1);
        stdVectorInts.swap(stdVectorInts1);

        ft::vector<int>::iterator ftIt = ftVectorInts.begin();
        std::vector<int>::iterator stdIt = stdVectorInts.begin();

        REQUIRE(*(ftIt) == *(stdIt));
    }
}