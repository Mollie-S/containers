#ifndef IS_ITERATOR_HPP
#define IS_ITERATOR_HPP

#include <iterator>
#include "iterator_traits.hpp"

namespace ft
{
    template<typename T, typename C = typename iterator_traits<T>::iterator_category> // first check if input_iterator is valid
    struct is_forward_iterator
	{
        typedef char yes[1];
        typedef char no[2];

        static yes& test(std::forward_iterator_tag);
        static no& test(...);

        static const bool value = (sizeof(test(C())) == sizeof(yes)); // returns empty(false) or type(true)
    };

    template<typename T, typename C = typename iterator_traits<T>::iterator_category> // first check if input_iterator is valid
    struct is_input_iterator
	{
        typedef char yes[1];
        typedef char no[2];

        static yes& test(std::input_iterator_tag);
        static no& test(...);

        static const bool value = (sizeof(test(C())) == sizeof(yes)); // returns empty(false) or type(true)
    };
}

#endif
