#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <stddef.h>
#include <stdbool.h>
#include <iostream>

#include "red_black_tree/rbtree.hpp"

#include "iterator/reverse_iterator.hpp"

#include "utility/lexicographical_compare.hpp"
#include "utility/equal.hpp"
#include "utility/pair.hpp"
#include "utility/is_integral.hpp"
#include "utility/enable_if.hpp"
#include "utility/ft_swap.hpp"

namespace ft
{
	template < class Key,                                     		// map::key_type
           class T,                                       			// map::mapped_type
           class Compare = ::std::less<Key>,                     	// map::key_compare
           class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
           >
    class map
	{
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

	private:
		typedef rbtree<value_type, key_compare, allocator_type, rbtree_node_for_map<value_type> > tree_type;

	public:
		typedef typename tree_type::iterator			iterator;
		typedef typename tree_type::const_iterator		const_iterator;
        typedef ft::reverse_iterator<iterator>          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

		class value_compare // Nested function class to compare elements
			: public ::std::binary_function<value_type, value_type, bool> { //  // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
			friend class map; // is part of the standard http://www.lirmm.fr/~ducour/Doc-objets/ISO+IEC+14882-1998.pdf 23.3.1 Template class map
		private:
			value_compare() {}
		protected:
			Compare comp; // Notice that value_compare has no public constructor, therefore no objects can be directly created from this nested class outside map members.
			value_compare(Compare c) : comp(c) {}

		public:
			typedef bool result_type;
  			typedef value_type first_argument_type;
  			typedef value_type second_argument_type;
  			bool operator()(const value_type& x, const value_type& y) const {
				return comp(x.first, y.first);
			}
			value_compare(const value_compare& other) : comp(other.comp) {}

			value_compare& operator=(const value_compare& other) {
				if (this != &other) {
					comp = other.comp;
				}
				return *this;
			}
		};

	private:
		tree_type	_tree;

	public:
		// CONSTRUCTORS:
		//empty (1)
		// _alloc(alloc), _node_alloc(alloc): allocator has got a template constructor that allows to construct an instance out of another type
		explicit map(const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type()) : _tree(comp, alloc) {}

		// range (2)
		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _tree(comp, alloc) 
		{
			insert(first, last);
		}

		// copy (3)
		map(const map& x): _tree(x._tree) 
		{
			insert(x.begin(), x.end());
		}
		
		~map() {}

		map& operator=(const map& x)
		{
			_tree = x._tree;
			return *this;
		}

		allocator_type get_allocator() const
		{
			return _tree.get_allocator();
		}
		
		// ELEMENT ACCESS:
		mapped_type& operator[](const key_type& k)
		{
			pair<key_type, mapped_type> pair = ft::make_pair(k, mapped_type());
			iterator inserted = insert(pair).first;
			return inserted->second;;
		}

		// ITERATORS:
	public:
		iterator begin()
		{
			return _tree.begin();
		}
		
		const_iterator begin() const
		{
			return _tree.begin();
		}

		iterator end()
		{
			return _tree.end();
		}

		const_iterator end() const
		{
			return _tree.end();
		}

		reverse_iterator rbegin()
		{
			return _tree.rbegin();
		}

		const_reverse_iterator rbegin() const
		{
			return _tree.rbegin();
		}

		reverse_iterator rend()
		{
			return _tree.rend();
		}

		const_reverse_iterator rend() const
		{
			return _tree.rend();
		}

		// CAPACITY:

		bool empty() const
		{
			return _tree.empty();
		}
		size_type max_size() const
		{
			return _tree.max_size();
		}
		size_type size() const
		{
			return _tree.size();
		}

		// MODIFIERS:
		void clear()
		{
			_tree.clear();
		}

		void erase(iterator position)
		{
			_tree.erase(position);
		}

		// can be implemented with found or equal range. Found also calls 2 functions inside it so the complaxity might be equal;
		size_type erase(const key_type& key)
		{
			return _tree.erase(key);
		}

		void erase(iterator first, iterator last)
		{
			_tree.erase(first, last);
		}

		// insert():
		// single element (1)	
		pair<iterator,bool> insert(const value_type& val)
		{
			return _tree.insert(val);
		}

		// with hint (2)
		iterator insert (iterator position, const value_type& val)
		{
			return _tree.insert(position, val);
		}

		// range (3)
		template <class InputIterator>
		void insert(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
		{
			_tree.insert(first, last);
		}

		//LOOKUP:
		size_type count(const key_type& key) const
		{
			return _tree.count(key);
		}

		//The range is defined by two iterators,
		// one pointing to the first element that is not less than key 
		//and another pointing to the first element greater than key. 
		//Alternatively, the first iterator may be obtained with lower_bound(), and the second with upper_bound().
		pair<iterator,iterator> equal_range(const key_type& key)
		{
			return _tree.equal_range(key);
		}

		pair<const_iterator,const_iterator> equal_range(const key_type& key) const
		{
			return _tree.equal_range(key);
		}

		iterator find(const Key& key )
		{
			return _tree.find(key);
		}

		const_iterator find(const key_type& key) const
		{
			return _tree.find(key);
		}
		
		//A similar member function, upper_bound, has the same behavior as lower_bound,
		// except in the case that the map contains an element with a key equivalent to k:
		// In this case, lower_bound returns an iterator pointing to that element,
		// whereas upper_bound returns an iterator pointing to the next element.
		iterator lower_bound(const key_type& key)
		{
			return _tree.lower_bound(key);
		}

		const_iterator lower_bound(const key_type& key) const
		{
			return _tree.lower_bound(key);
		}
		
		// returns the iterator pointing to the element > than the key
		iterator upper_bound (const key_type& key)
		{
			return _tree.upper_bound(key);
		}
		
		const_iterator upper_bound (const key_type& key) const
		{
			return _tree.upper_bound(key);
		}
		
		// OBSERVERS:
		key_compare key_comp() const
		{
			return _tree.key_comp();
		}
		value_compare value_comp() const
		{
			return value_compare(_tree.key_comp());
		}

		void swap(map& other )
		{
			_tree.swap(other._tree);
		}

		// void tree_print_helper()
		// {
		// 	_tree.tree_print_helper();
		// }
	};

	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs )
	{
		lhs.swap(rhs);
	}

   //relational operators (map):
	template <class Key, class T, class Compare, class Alloc>
	bool operator==( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=( const map<Key,T,Compare,Alloc>& lhs,const map<Key,T,Compare,Alloc>& rhs )
	{
        return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<( const map<Key,T,Compare,Alloc>& lhs,const map<Key,T,Compare,Alloc>& rhs )
	{
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=( const map<Key,T,Compare,Alloc>& lhs,const map<Key,T,Compare,Alloc>& rhs )
	{
        return !(rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>( const map<Key,T,Compare,Alloc>& lhs,const map<Key,T,Compare,Alloc>& rhs )
	{
        return rhs < lhs;
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=( const map<Key,T,Compare,Alloc>& lhs,const map<Key,T,Compare,Alloc>& rhs )
	{
        return !(lhs < rhs);
	}
}

#endif
