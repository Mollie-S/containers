#ifndef RBTREE_ITERATOR_HPP
#define RBTREE_ITERATOR_HPP

#include "rbtree_node.hpp"
#include "iterator/iterator_traits.hpp"

namespace ft
{
	template <class Value, typename NodeBase, typename Node>
	class rbtree_iter
	{
	public:
		typedef rbtree_iter<Value, NodeBase, Node>		iterator_type;
		typedef std::bidirectional_iterator_tag			iterator_category;
		typedef Value        							value_type;
    	typedef ptrdiff_t  								difference_type;
    	typedef Value*         							pointer;
    	typedef Value&         							reference;

	private:
		typedef Node* NodePtr;
		typedef rbtree_iter<const Value, const NodeBase, const Node> const_iterator_type;
	
	protected:
		typedef NodeBase* NodeBasePtr;

		NodeBasePtr _node_ptr;

		bool isSentinel(NodeBasePtr node_ptr) const
		{
			return (node_ptr->_left == NULL && node_ptr->_right == NULL);
		}

	public:
		rbtree_iter() : _node_ptr(NULL) {}
		rbtree_iter(NodeBasePtr node_ptr) : _node_ptr(node_ptr) {}
		rbtree_iter(const iterator_type& other) : _node_ptr(other._node_ptr) {}
		~rbtree_iter(){};

		rbtree_iter& operator=(const rbtree_iter& other)
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
		// type conversion operator
		operator const_iterator_type() const
		{
			return const_iterator_type(_node_ptr);
		}

		difference_type	distance(rbtree_iter first, rbtree_iter last)
		{
			difference_type count = 0;
			rbtree_iter it = first;
			while (it != last)
			{
				count++;
				it++;
			}
			return count;
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
		rbtree_iter& operator++()
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

		rbtree_iter operator++(int) // postfix operator as it accepts an argument
		{
			rbtree_iter temp = *this;
			++(*this);
			return temp;
		}

		rbtree_iter& operator--()
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
		
		rbtree_iter operator--(int)
		{
			rbtree_iter temp = *this;
			--(*this);
			return temp;
		}

	// will be able to convert non-const to const due to conversion operator
		friend
		bool operator==(const iterator_type& lhs, const iterator_type& rhs)
		{
			return (lhs._node_ptr == rhs._node_ptr);
		}

		friend
		bool operator!=(const iterator_type& lhs, const iterator_type& rhs)
		{
			return (lhs._node_ptr != rhs._node_ptr);
		}
	};
}
#endif

