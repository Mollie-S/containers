#define CONFIG_CATCH_MAIN
#include "catch.hpp"
#include "../stack.hpp"
#include <stack>

ft::stack<int> ftStackInts;
std::stack<int> stdStackInts;

TEST_CASE("Creating a container", "[empty]")
{
    REQUIRE(ftStackInts.empty() == stdStackInts.empty());
}