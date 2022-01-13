#ifndef SET_HPP
#define SET_HPP

#include <memory>
#include <stddef.h>
#include <stdbool.h>
#include <iostream>

#include "../utility/lexicographical_compare.hpp"
#include "../utility/equal.hpp"
#include "../utility/pair.hpp"
#include "../utility/reverse_iterator.hpp"
#include "../utility/is_integral.hpp"
#include "../utility/enable_if.hpp"
#include "../utility/ft_swap.hpp"
#include "../red_black_tree/rbtree.hpp"

namespace ft
{
	
	template < class T,                        // set::key_type/value_type
           class Compare = ::std::less<T>,        // set::key_compare/value_compare
           class Alloc = ::std::allocator<T>      // set::allocator_type
           >
	class set
	{
    public:
        typedef T											key_type;
        typedef T											value_type;
        typedef Compare										key_compare;
        typedef Compare										value_compare;
        typedef Alloc										allocator_type;
        typedef value_type&									reference;
        typedef const value_type&							const_reference;
		typedef typename allocator_type::pointer        	pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;

	private:
		typedef rbtree<value_type, key_compare, allocator_type, rbtree_node_for_set<value_type> > tree_type;

	public:
		typedef typename tree_type::iterator			iterator;
		typedef typename tree_type::const_iterator		const_iterator;
        typedef ft::reverse_iterator<iterator>          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

	private:
		tree_type	_tree;

	public:
		// CONSTRUCTORS:
		//empty (1)
		// _alloc(alloc), _node_alloc(alloc): allocator has got a template constructor that allows to construct an instance out of another type
		explicit set(const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type()) : _tree(comp, alloc) {}

		// range (2)
		template <class InputIterator>
		set(InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _tree(comp, alloc) 
		{
			insert(first, last);
		}

		// copy (3)
		set(const set& x): _tree(x._tree) 
		{
			insert(x.begin(), x.end());
		}
		
		~set() {}

		set& operator=(const set& x)
		{
			_tree = x._tree;
			return *this;
		}

		allocator_type get_allocator() const
		{
			return _tree.get_allocator();
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
		size_type erase(const value_type& key)
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

		//OPERATIONS:
		size_type count(const value_type& key) const
		{
			return _tree.count(key);
		}

		//The range is defined by two iterators,
		// one pointing to the first element that is not less than key 
		//and another pointing to the first element greater than key. 
		//Alternatively, the first iterator may be obtained with lower_bound(), and the second with upper_bound().
		pair<iterator,iterator> equal_range(const value_type& key)
		{
			return _tree.equal_range(key);
		}

		pair<const_iterator,const_iterator> equal_range(const value_type& key) const
		{
			return _tree.equal_range(key);
		}

		iterator find(const value_type& key )
		{
			return _tree.find(key);
		}

		const_iterator find(const value_type& key) const
		{
			return _tree.find(key);
		}
		
		//A similar member function, upper_bound, has the same behavior as lower_bound,
		// except in the case that the set contains an element with a key equivalent to k:
		// In this case, lower_bound returns an iterator pointing to that element,
		// whereas upper_bound returns an iterator pointing to the next element.
		iterator lower_bound(const value_type& key)
		{
			return _tree.lower_bound(key);
		}

		const_iterator lower_bound(const value_type& key) const
		{
			return _tree.lower_bound(key);
		}
		
		// returns the iterator pointing to the element > than the key
		iterator upper_bound (const value_type& key)
		{
			return _tree.upper_bound(key);
		}
		
		const_iterator upper_bound (const value_type& key) const
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
			return key_comp();
		}

		void swap(set& other )
		{
			_tree.swap(other._tree);
		}

		// void tree_print_helper()
		// {
		// 	_tree.tree_print_helper();
		// }
	};

	template< class T, class Compare, class Alloc >
	void swap( ft::set<T,Compare,Alloc>& lhs, ft::set<T,Compare,Alloc>& rhs )
	{
		lhs.swap(rhs);
	}

   //relational operators (set):
	template <class T, class Compare, class Alloc>
	bool operator==( const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs )
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class T, class Compare, class Alloc>
	bool operator!=( const set<T,Compare,Alloc>& lhs,const set<T,Compare,Alloc>& rhs )
	{
        return !(lhs == rhs);
	}

	template <class T, class Compare, class Alloc>
	bool operator<( const set<T, Compare,Alloc>& lhs,const set<T,Compare,Alloc>& rhs )
	{
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Compare, class Alloc>
	bool operator<=( const set<T,Compare,Alloc>& lhs,const set<T,Compare,Alloc>& rhs )
	{
        return !(rhs < lhs);
	}

	template <class T, class Compare, class Alloc>
	bool operator>( const set<T, Compare,Alloc>& lhs,const set<T,Compare,Alloc>& rhs )
	{
        return rhs < lhs;
	}

	template <class T, class Compare, class Alloc>
	bool operator>=( const set<T,Compare,Alloc>& lhs,const set<T,Compare,Alloc>& rhs )
	{
        return !(lhs < rhs);
	}
}

#endif
