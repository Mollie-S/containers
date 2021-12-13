#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <iostream>
#include "reverse_iterator.hpp"


namespace ft{
    template < class Key, class T,class Compare = ::std::less<Key>,
           class Alloc = ::std::allocator<::std::pair<const Key,T> > > // pair must be reimplemented!!!
    class map {
    public:

        typedef Key											key_type;
        typedef T											mapped_type;
        typedef std::pair<const key_type, mapped_type>		value_type;
        typedef Compare										key_compare;
        typedef Alloc										allocator_type;
        typedef value_type&									reference;
        typedef const value_type&							const_reference;
		typedef typename allocator_type::pointer        	pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;

		// TODO: 
		// a bidirectional iterator to value_type			iterator;
		// a bidirectional iterator to value_type			const_iterator;

		// typedef reverse_iterator<iterator>               reverse_iterator;
		// typedef reverse_iterator<const_iterator>         const_reverse_iterator;


		static_assert(sizeof(__diagnose_non_const_comparator<_Key, _Compare>()), "");
		static_assert((is_same<typename allocator_type::value_type, value_type>::value),
					"Allocator::value_type must be same type as value_type");


		class value_compare // Nested function class to compare elements
			: public ::std::binary_function<value_type, value_type, bool> { //  // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
			friend class map;
		protected:
			Compare comp; // Notice that value_compare has no public constructor, therefore no objects can be directly created from this nested class outside map members.
			value_compare(Compare c) : comp(c) {} // // constructed with map's comparison object
		public:
			typedef bool result_type;
  			typedef value_type first_argument_type;
  			typedef value_type second_argument_type;
  			bool operator()(const value_type& x, const value_type& y) const {
				return comp(x.first, y.first);
			}
		};
    };
};

#endif