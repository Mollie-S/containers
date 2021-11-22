#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

#include "false_type.hpp"
#include "true_type.hpp"

template<typename> struct is_integral_base : ft::false_type {};

template<> struct is_integral_base<bool>: ft::true_type {};
template<> struct is_integral_base<int>: ft::true_type {};
template<> struct is_integral_base<short> : ft::true_type {};
template<> struct is_integral_base<long> : ft::true_type {};
template<> struct is_integral_base<char> : ft::true_type {};
template<> struct is_integral_base<wchar_t> : ft::true_type {};

template<> struct is_integral_base<const bool> : ft::true_type {};
template<> struct is_integral_base<const int>: ft::true_type {};
template<> struct is_integral_base<const short> : ft::true_type {};
template<> struct is_integral_base<const long> : ft::true_type {};
template<> struct is_integral_base<const char> : ft::true_type {};
template<> struct is_integral_base<const wchar_t> : ft::true_type {};


template<typename T>
struct is_integral : is_integral_base<std::remove_cv_t<T>> {}; // IMPLEMENTING REMOVE_CV_T? OR LEAVING CONST ?




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
