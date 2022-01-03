#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP




// Common technique for algorithm selection based on iterator category tags i
//s to use a dispatcher function (the alternative is std::enable_if). 
namespace ft
{
    template<bool B, class T = void>
    struct enable_if {};

    // if the condition (given instead of true in prototype) is true, it returns the type. If not nothing happens
    template<class T>
    struct enable_if<true, T> 
    { 
        typedef T type; 
    };
}

#endif
