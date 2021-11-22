#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

template<bool B, class T = void>
struct enable_if {};

// if the condition (given instead of true in prototype) is true returns the type if not nothing happens
template<class T>
struct enable_if<true, T> { typedef T type; };

// std::enable_if_t is a type alias of the inner ::type of std::enable_if,
// it's syntactic sugar so you don't have to write
// typename std::enable_if</* */>::type




template< class Iter >
struct iterator_traits;
template< class T >
struct iterator_traits<T*>;
template< class T >
struct iterator_traits<const T*>;

template<class T> is_iterator : public integral_constant<bool, !is_integral<T>::value>{

	};

#endif
