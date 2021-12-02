#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

#include "is_integral.hpp"

namespace ft
{
    template<bool B, class T = void>
    struct enable_if {};

    // if the condition (given instead of true in prototype) is true returns the type if not nothing happens
    template<class T>
    struct enable_if<true, T> { typedef T type; };
}

// std::enable_if_t is a type alias of the inner ::type of std::enable_if,
// it's syntactic sugar so you don't have to write
// typename std::enable_if</* */>::type

#endif
