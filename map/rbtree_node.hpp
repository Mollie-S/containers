#ifndef RBTREE_NODE_HPP
#define RBTREE_NODE_HPP

#include "../utility/pair.hpp"

enum color_t { BLACK, RED };
typedef enum color_t e_color;

namespace ft 
{
	template <class Key, class T>
	struct rbtree_node
	{
		rbtree_node*				_parent;
		rbtree_node*				_left;
		rbtree_node*				_right;
		e_color 					_color;
		ft::pair<const Key, T> 		_value;
		explicit rbtree_node(const rbtree_node& value): _parent(NULL), _left(NULL), _right(NULL), _color(BLACK), _value(value) {}
	};
}

#endif
