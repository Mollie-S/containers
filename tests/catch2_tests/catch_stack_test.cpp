#include "include/catch.hpp"

#include "stack.hpp"
#include "vector.hpp"
#include <stack>
#include <vector>

TEST_CASE("Constructing a stack and manipulating elements in it", "[string keys]")
{
    ft::stack<std::string> my_stack;
    std::stack<std::string> st_stack;
    SECTION("Testing empty() function")
    {
        CHECK(my_stack.empty() == st_stack.empty());

        SECTION("Pushing values to the stack")
        {
            my_stack.push("red");
            st_stack.push("red");
            my_stack.push("blue");
            st_stack.push("blue");
            my_stack.push("black");
            st_stack.push("black");
            CHECK(my_stack.top() == st_stack.top());
            
            SECTION("Stack copy constructor called")
            {
                ft::stack<std::string> my_copy(my_stack);
                std::stack<std::string> st_copy(st_stack);
                CHECK(my_copy == my_stack);
                CHECK(st_copy == st_stack);
                CHECK(st_copy.top() == my_copy.top());
                CHECK(st_copy.size() == my_copy.size());

                SECTION("Popping values from copy - original is unchanged")
                {
                    my_copy.pop();
                    my_copy.pop();
                    my_copy.pop();
                    st_copy.pop();
                    st_copy.pop();
                    st_copy.pop();
                    CHECK(my_copy.size() == 0);
                    CHECK(my_copy != my_stack);
                    CHECK(my_copy < my_stack);
                    CHECK(my_stack > my_copy);

                    SECTION("Assignment operator - values are assigned again")
                    {
                        my_copy = my_stack;
                        CHECK(my_copy == my_stack);
                        CHECK(my_copy.size() == my_stack.size());
                    }
                }
            }
        }
    }
}

