#define CATCH_CONFIG_MAIN 
#include "catch.hpp"

#include "../vector/vector.hpp"
#include <vector>

ft::vector<int> ftVectorInts;
std::vector<int> stdVectorInts;

TEST_CASE("Creating a container", "[empty]")
{
    REQUIRE(ftVectorInts.empty() != stdVectorInts.empty());
}
