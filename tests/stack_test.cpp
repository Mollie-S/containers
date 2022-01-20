
#include "../vector/vector.hpp"
#include "../stack/stack.hpp"
#include <vector>
#include <stack>

#include "catch.hpp"

ft::stack<int> ftStackInts;
std::stack<int> stdStackInts;

TEST_CASE("Creating a container", "[empty]")
{
    REQUIRE(ftStackInts.empty() == stdStackInts.empty());
}

TEST_CASE("Pushing a value", "[empty]")
{
    ftStackInts.push(89);
    stdStackInts.push(89);
    REQUIRE(ftStackInts.top() == stdStackInts.top());
}

TEST_CASE("'Is it stack' check", "")
{
    REQUIRE(ftStackInts.empty() == stdStackInts.empty());
}
