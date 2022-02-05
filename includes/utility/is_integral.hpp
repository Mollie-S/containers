#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

#include "false_type.hpp"
#include "true_type.hpp"
#include "remove_cv.hpp"

// Note that std::false_type and std::true_type are specializations of std::integral_constant.

namespace ft
{
    template<typename> struct is_integral_helper : ft::false_type {};

    template<> struct is_integral_helper<bool>: ft::true_type {};
    template<> struct is_integral_helper<int>: ft::true_type {};
    template<> struct is_integral_helper<short> : ft::true_type {};
    template<> struct is_integral_helper<long> : ft::true_type {};
    template<> struct is_integral_helper<char> : ft::true_type {};
    template<> struct is_integral_helper<wchar_t> : ft::true_type {};

    template<typename T>
    struct is_integral: public is_integral_helper<typename ft::remove_cv<T>::type >{};
}

// Fundamental types in C++ are divided into three categories: 
// integral, floating point, and void.
// Integral types are capable of handling whole numbers. Includes the following datatypes-
// char
// bool
// short
// int
// long
// long long
// wchar_t, __wchar_t

// Floating point types are capable of specifying values that may have fractional parts.
// float
// double
// long double

// The void type describes an empty set of values.

#endif
