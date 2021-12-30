#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "rbtree_node.hpp"

// TODO : remove when iterator_traits implemented
namespace ft
{
	template <class Value>
	class map_iter;
}

namespace std {
	template<typename Value> 
	struct iterator_traits<ft::map_iter<Value> >
	{
		typedef Value        	value_type;
    	typedef std::size_t   	difference_type;
    	typedef Value*         	pointer;
    	typedef Value&         	reference;
	};
}

namespace ft
{
	template <class Value>
	class map_iter // Iterator base class
	{
		//TODO
		// replace std with ft when iterator_traits implemented:
	public:
		
		// typedef Value							                      			iterator_type;
		// typedef typename ::std::bidirectional_iterator_tag                      	iterator_category;
		// typedef typename ::std::iterator_traits<iterator_type>::value_type        	value_type;
    	// typedef typename ::std::iterator_traits<iterator_type>::difference_type   	difference_type;
    	// typedef typename ::std::iterator_traits<iterator_type>::pointer           	pointer;
    	// typedef typename ::std::iterator_traits<iterator_type>::reference         	reference;

		typedef map_iter<Value>							                      		iterator_type;
		typedef typename ::std::bidirectional_iterator_tag                      	iterator_category;
		typedef typename ::std::iterator_traits<iterator_type>::value_type        	value_type;
    	typedef typename ::std::iterator_traits<iterator_type>::difference_type   	difference_type;
    	typedef typename ::std::iterator_traits<iterator_type>::pointer           	pointer;
    	typedef typename ::std::iterator_traits<iterator_type>::reference         	reference;

		// typedef Value        	value_type;
    	// typedef std::size_t   	difference_type;
    	// typedef Value*         	pointer;
    	// typedef Value&         	reference;

	private:
		rbtree_node_base* _node_ptr;

		bool isSentinel(rbtree_node_base* node_ptr) const
		{
			return (node_ptr->_left == NULL && node_ptr->_right == NULL);
		}

	public:
		map_iter() : _node_ptr(NULL) {}
		map_iter(rbtree_node_base* node_ptr) : _node_ptr(node_ptr) {}
		map_iter(const map_iter& other) : _node_ptr(other._node_ptr) {}
		~map_iter(){};

		// difference_type	distance(map_iter first, map_iter last)
		// {
		// 	difference_type count = 0;
		// 	while (first + count != last)
		// 		count++;
		// 	return count;
		// }
		map_iter& operator=(const map_iter& other)
		{
			if (*this != other)
			{
				_node_ptr = other._node_ptr;
			}
			return (*this);
		}
		reference operator*() const
		{
			assert(!isSentinel(_node_ptr));
			return (static_cast<rbtree_node<Value>* >(_node_ptr)->_value); // we can downcast here as we are sure that it's not the base node(only sentinels are base ones)
		}
		pointer operator->() const
		{
			assert(!isSentinel(_node_ptr));
			return (&static_cast<rbtree_node<Value>* >(_node_ptr)->_value);
		}

	private:
		rbtree_node_base* _move_down_right(rbtree_node_base* node_ptr)
		{
			if (!isSentinel(node_ptr->_right))
			{
				node_ptr = node_ptr->_right;
				while (!isSentinel(node_ptr->_left))
				{
					node_ptr = node_ptr->_left;
				}
			}
			return node_ptr;
		}
		rbtree_node_base* _move_down_left(rbtree_node_base* node_ptr)
		{
			if (!isSentinel(node_ptr->_left))
			{
				node_ptr = node_ptr->_left;
				while (!isSentinel(node_ptr->_right))
				{
					node_ptr = node_ptr->_right;
				}
			}
			return node_ptr;
		}
		rbtree_node_base* _move_up(rbtree_node_base* node_ptr, std::string moving_direction)
		{
			rbtree_node_base* side_leading_to_visited_parent;
			if (moving_direction == "right")
			{
				side_leading_to_visited_parent = node_ptr->_parent->_right;
			}
			else
			{
				side_leading_to_visited_parent = node_ptr->_parent->_left;
			}
			while (node_ptr == side_leading_to_visited_parent) // means that we have already visited that parent node before and need to move up again
			{
				node_ptr = node_ptr->_parent; // returning to the visited parent
			}
			node_ptr = node_ptr->_parent; // moving up to the non-visited parent
			return node_ptr;
		}

	public:
 		//  ARITHMETIC OPERATORS
		map_iter& operator++()
		{
			if (!isSentinel(_node_ptr->_right))
			{
				_node_ptr = _move_down_right(_node_ptr);
			}
			else
			{
				_node_ptr = _move_up(_node_ptr, "right");
			}
			return *this;
		}

		map_iter operator++(int) // postfix operator as it accepts an argument
		{
			map_iter temp = *this;
			++(*this);
			return temp;
		}

		map_iter& operator--()
		{
			// // if we're decrementing an iterator pointing to end():
			// if (isSentinel(_node_ptr))
			// {
			// 	rbtree_node_base *node = _root;
			// 	while (!isSentinel(_node_ptr->_right)) // iterating until the left are not pointing to the NIL that is the sentinel node
			// 	{
			// 		node = node->_right;
			// 	}
			// 	_node_ptr = node;
			// 	return *this;
			// }
			if (!isSentinel(_node_ptr->_left))
			{
				_node_ptr = _move_down_left(_node_ptr);
			}
			else
			{
				_node_ptr = _move_up(_node_ptr, "left");
			}
			return *this;
		}
		map_iter operator--(int)
		{
			map_iter temp = *this;
			--(*this);
			return temp;
		}
// 		map_iter& operator+=(const int &val)
// 		{
// 			_ptr += val;
// 			return (*this);
// 		}
// 		map_iter& operator-=(const int &val)
// 		{
// 			_ptr -= val;
// 			return (*this);
// 		}
// 		// RELATIONAL OPERATORS
// 		bool operator<(const map_iter& rhs) const
// 		{
// 			return _ptr < rhs._ptr;
// 		}
// 		bool operator>(const map_iter& rhs)
// 		{
// 			return _ptr > rhs._ptr;
// 		}
// 		bool operator<=(const map_iter& rhs) const
// 		{
// 			return _ptr <= rhs._ptr;
// 		}
// 		bool operator>=(const map_iter& rhs)
// 		{
// 			return _ptr >= rhs._ptr;
// 		}
// 		friend map_iter operator+(const map_iter& lhs, const int rhs)
// 		{
// 			return (lhs._ptr + rhs);
// 		}
// 		friend map_iter operator-(const map_iter& lhs, const int rhs)
// 		{
// 			return (lhs._ptr - rhs);
// 		}
// 		friend difference_type operator-(const map_iter& lhs, const map_iter& rhs)
// 		{
// 			return (lhs._ptr - rhs._ptr);
// 		}
// 		friend bool operator==(const map_iter& lhs, const map_iter& rhs)
// 		{
// 			return (lhs._ptr == rhs._ptr);
// 		}
		friend bool operator!=(const map_iter& lhs, const map_iter& rhs) { return !(lhs._node_ptr == rhs._node_ptr); }
	};

}
#endif
