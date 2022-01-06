#ifndef MAP_ITERATOR_COPY_WITH_FRIEND_HPP
#define MAP_ITERATOR_COPY_WITH_FRIEND_HPP

#include "rbtree_node.hpp"
#include "../utility/iterator_traits.hpp"

// THIS IS THE COPY OF THE MAP CLASS. 
// DIFFERS FROM THE ORIGINAL ONE BY THE USE OF THE FRIEND KEYWORD FOR ACESSING THE PRIVATE ATTRIBUTE _NODE_PTR IN THE MAP_ITER
// AND MAP_ITER SPECIALIZATION FOR ANY TYPE(NEEDED FOR CONST TYOE ITERATOR)
// THESE CASES OF USING 'FRIEND' ARE FORBIDDEN BY THE PROJECT SUBJECT
// BUT I THINK THEY ARE BETTER FIT FOR CONVERTING NON-CONST ITERATOR TYPES TO CONST


namespace ft
{
	template <class Key,
			  class T,		
			  class Compare,
			  class Alloc
			  >
	class map;

	template <class Value, typename NodeBasePtr, typename NodePtr>
	class map_iter // Iterator base class
	{
	public:
		typedef map_iter<Value, NodeBasePtr, NodePtr>	                      	iterator_type;
		typedef typename ft::iterator_traits<iterator_type>::iterator_category 	iterator_category;
		typedef typename ft::iterator_traits<iterator_type>::value_type        	value_type;
    	typedef typename ft::iterator_traits<iterator_type>::difference_type   	difference_type;
    	typedef typename ft::iterator_traits<iterator_type>::pointer           	pointer;
    	typedef typename ft::iterator_traits<iterator_type>::reference         	reference;

		// maps of any specialization are allowed to see private members
		template<typename T1, typename T2, typename T3, typename T4>
		friend class map;

		// means that map_iter specialized for any types can get access to the map iter of these types
		// crazy
		template<typename T1, typename T2, typename T3>
		friend class map_iter;

	private:
		NodeBasePtr _node_ptr;

		bool isSentinel(NodeBasePtr node_ptr) const
		{
			return (node_ptr->_left == NULL && node_ptr->_right == NULL);
		}

	public:
		map_iter() : _node_ptr(NULL) {}
		map_iter(NodeBasePtr node_ptr) : _node_ptr(node_ptr) {}
		
		// template function inside of a template accepting map_iter for the same value type but with different node pointers
		// this allows to cast from non-const to const
		template <typename T1, typename T2>
		map_iter(const map_iter<Value, T1, T2> &other) : _node_ptr(other._node_ptr) {}
		~map_iter(){};

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
			return (static_cast<NodePtr>(_node_ptr)->_value); // we can downcast here as we are sure that it's not the base node(only sentinels are base ones)
		}
		pointer operator->() const
		{
			assert(!isSentinel(_node_ptr));
			return (&static_cast<NodePtr>(_node_ptr)->_value);
		}

	private:
		NodeBasePtr _move_down_right(NodeBasePtr node_ptr)
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
		NodeBasePtr _move_down_left(NodeBasePtr node_ptr)
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


		NodeBasePtr _move_up_left(NodeBasePtr node_ptr)
		{
			while (node_ptr == node_ptr->_parent->_left) // means that we have already visited that parent node before and need to move up again
			{
				node_ptr = node_ptr->_parent; // returning to the visited parent
			}
			node_ptr = node_ptr->_parent; // moving up to the non-visited parent
			return node_ptr;
		}
		NodeBasePtr _move_up_right(NodeBasePtr node_ptr)
		{
			while (node_ptr == node_ptr->_parent->_right) // means that we have already visited that parent node before and need to move up again
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
			// if we're incrementing a reverse_iterator pointing to rend():
			if (isSentinel(_node_ptr))
			{
				rbtree_node_base *node = _node_ptr->_parent; // sentinel's parent is always pointing to the root
				while (!isSentinel(node->_left)) // iterating until the right is not pointing to the NIL that is the sentinel node
				{
					node = node->_left;
				}
				_node_ptr = node;
				return *this;
			}
			if (!isSentinel(_node_ptr->_right))
			{
				_node_ptr = _move_down_right(_node_ptr);
			}
			else
			{
				_node_ptr = _move_up_right(_node_ptr);
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
			// if we're decrementing an iterator pointing to end():
			if (isSentinel(_node_ptr))
			{
				rbtree_node_base *node = _node_ptr->_parent; // sentinel's parent is always pointing to the root
				while (!isSentinel(node->_right)) // iterating until the right is not pointing to the NIL that is the sentinel node
				{
					node = node->_right;
				}
				_node_ptr = node;
				return *this;
			}
			if (!isSentinel(_node_ptr->_left))
			{
				_node_ptr = _move_down_left(_node_ptr);
			}
			else
			{
				_node_ptr = _move_up_left(_node_ptr);
			}
			return *this;
		}
		map_iter operator--(int)
		{
			map_iter temp = *this;
			--(*this);
			return temp;
		}

		// EQUALITY/INEQUALITY OPERATORS:
		template<typename T1, typename T2>
		bool operator==(const map_iter<Value, T1, T2>& other) const
		{
			return (_node_ptr == other._node_ptr);
		}

		template<typename T1, typename T2>
		bool operator!=(const map_iter<Value, T1, T2>& other) const
		{
			return (_node_ptr != other._node_ptr);
		}
	};
}
#endif
