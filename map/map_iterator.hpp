#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "rbtree_node.hpp"

// TODO : remove when iterator_traits implemented
namespace ft
{
	template <class Value, typename NodeBasePtr, typename NodePtr>
	class map_iter;
}

namespace std {
	template<typename Value, typename T1, typename T2> 
	struct iterator_traits<ft::map_iter<Value, const T1*, const T2*> >
	{
		typedef Value        	value_type;
    	typedef std::size_t   	difference_type;
    	typedef const Value*    pointer;
    	typedef const Value&    reference;
	};

	template<typename Value, typename T1, typename T2> 
	struct iterator_traits<ft::map_iter<Value, T1*, T2*> >
	{
		typedef Value        	value_type;
    	typedef std::size_t   	difference_type;
    	typedef Value*         	pointer;
    	typedef Value&         	reference;
	};
}

namespace ft
{

	template <class Value, typename NodeBasePtr, typename NodePtr>
	class map_iter // Iterator base class
	{
	
		//TODO
		// replace std with ft when iterator_traits implemented:
	public:


		typedef map_iter<Value, NodeBasePtr, NodePtr>	                      		iterator_type;
		typedef typename ::std::bidirectional_iterator_tag                      	iterator_category;
		typedef typename ::std::iterator_traits<iterator_type>::value_type        	value_type;
    	typedef typename ::std::iterator_traits<iterator_type>::difference_type   	difference_type;
    	typedef typename ::std::iterator_traits<iterator_type>::pointer           	pointer;
    	typedef typename ::std::iterator_traits<iterator_type>::reference         	reference;

		// typedef Value        	value_type;
    	// typedef std::size_t   	difference_type;
    	// typedef Value*         	pointer;
    	// typedef Value&         	reference;

	
	NodeBasePtr get_node_pointer() const
	{
		return _node_ptr;
	}
	//TODO: do I ever use it?
	// void set_node_pointer(NodeBasePtr ptr)
	// {
	// 	_node_ptr = ptr;
	// }

	private:
		NodeBasePtr _node_ptr;

		bool isSentinel(NodeBasePtr node_ptr) const
		{
			return (node_ptr->_left == NULL && node_ptr->_right == NULL);
		}

	public:
		map_iter() : _node_ptr(NULL) {}
		map_iter(NodeBasePtr node_ptr) : _node_ptr(node_ptr) {}
		map_iter(const map_iter& other) : _node_ptr(other._node_ptr) {}
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
				while (!isSentinel(node->_right)) // iterating until the left are not pointing to the NIL that is the sentinel node
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

		friend bool operator==(const map_iter& lhs, const map_iter& rhs)
		{
			return (lhs._node_ptr == rhs._node_ptr);
		}
		friend bool operator!=(const map_iter& lhs, const map_iter& rhs) { return !(lhs._node_ptr == rhs._node_ptr); }
	};

}
#endif
