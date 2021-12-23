#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <stdbool.h>
#include <iostream>
#include "rbtree_node.hpp"


namespace ft
{
	template < class Key,                                     		// map::key_type
           class T,                                       			// map::mapped_type
           class Compare = ::std::less<Key>,                     	// map::key_compare
           class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
           >
    class map {
    public:

        typedef Key											key_type;
        typedef T											mapped_type;
        typedef ft::pair<const key_type, mapped_type>		value_type;
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


		// static_assert(sizeof(__diagnose_non_const_comparator<_Key, _Compare>()), "");
		// static_assert((is_same<typename allocator_type::value_type, value_type>::value),
		// 			"Allocator::value_type must be same type as value_type");


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
	private:
		typedef ft::rbtree_node<const Key,T>*	node_pointer;


		// explanation for rebind: 
		// The _Alloc template is used to obtain objects of some type. The container may have an internal need to allocate objects of a different type. For example, when you have a std::list<T, A>, the allocator A is meant to allocate objects of type T but the std::list<T, A> actually needs to allocate objects of some node type. Calling the node type _Ty, the std::list<T, A> needs to get hold of an allocator for _Ty objects which is using the allocation mechanism provided by A. Using
		// typename _A::template rebind<_Ty>::other
		// specifies the corresponding type. Now, there are a few syntactic annoyances in this declaration:
		// Since rebind is a member template of _A and _A is a template argument, the rebind becomes a dependent name. To indicate that a dependent name is a template, it needs to be prefixed by template. Without the template keyword the < would be considered to be the less-than operator.
		// The name other also depends on a template argument, i.e., it is also a dependent name. To indicate that a dependent name is a type, the typename keyword is needed.
		typedef typename Alloc::template rebind<ft::rbtree_node<const Key, T> >::other node_allocator;

		node_pointer	_root;
		node_allocator	_node_alloc;
		size_type       _size;
		value_compare	_comp;

		
		node_pointer allocate_node(const value_type& value)
		{
			node_pointer new_node = _node_alloc.allocate(1); //Attempts to allocate a block of storage with a size large enough to contain n elements of member type value_type (an alias of the allocator's template parameter), and returns a pointer to the first element.
			_node_alloc.construct(new_node, value);
			return new_node;
		}

		node_pointer create_node(const value_type& value)
		{
			node_pointer new_node = allocate_node(value);
			new_node->_color = RED;
			new_node->_parent = NULL;
			new_node->_left = NULL;
			new_node->_right = NULL;
		}

		bool isRed(node_pointer node) 
		{  
			if (node == NULL) 
				return false;
			return node->_color == RED;
		} 

public:
		// // TODO:
		// // CONSTRUCTORS:
		// //empty (1)	
		explicit map (const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type())
					 : _size(0), _node_alloc(alloc), _comp(comp), _root(NULL) {} // allocator has got a template constructor that allows to construct an instance out of another type

		// // range (2)
		// template <class InputIterator>
		// map (InputIterator first, InputIterator last,
		// 	const key_compare& comp = key_compare(),˜
		// 	const allocator_type& alloc = allocator_type());
		// // copy (3)
		// map (const map& x);

		
		
    };

}

#endif
