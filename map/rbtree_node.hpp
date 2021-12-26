#ifndef RBTREE_NODE_HPP
#define RBTREE_NODE_HPP

#include "../utility/pair.hpp"

enum color_t { BLACK, RED };
typedef enum color_t e_color;

namespace ft 
{


	struct rbtree_node_base
	{
		rbtree_node_base*		_parent;
		rbtree_node_base*		_left;
		rbtree_node_base*		_right;
		e_color 				_color;

		rbtree_node_base() : _parent(NULL), _left(NULL), _right(NULL), _color(BLACK) {}
	};
	//Here, we pass the derived class Node<Val> as a template argument to its own base (Node_base).
	// That allows Node_base to use Node<Val> in its interfaces without even knowing its real name!
	template <class Key, class T>
	struct rbtree_node : public rbtree_node_base<rbtree_node<Key, T>
	{
		ft::pair<const Key, T> 	_value;
		explicit rbtree_node(const rbtree_node& value): _value(value) {}
	};
}

#endif
