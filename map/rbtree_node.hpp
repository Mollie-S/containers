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
		// TODO: remove temp key from base and derived class
		std::string _key;

		rbtree_node_base(rbtree_node_base* parent_ptr, rbtree_node_base* child_ptr)
			: _parent(parent_ptr)
			, _left(child_ptr)
			, _right(child_ptr)
			, _color(RED)
			, _key("nothing")
			{}
	};

	//Here, we pass the derived class Node<Val> as a template argument to its own base (Node_base).
	// That allows Node_base to use Node<Val> in its interfaces without even knowing its real name!
	template <typename Value>
	struct rbtree_node : public rbtree_node_base
	{
		Value 	_value;
		explicit rbtree_node(rbtree_node_base *parent_ptr, rbtree_node_base *child_ptr, const Value &value)
			: rbtree_node_base(parent_ptr, child_ptr), _value(value) { _key = value.first; }
	};
}

#endif
