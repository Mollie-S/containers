#ifndef RBTREE_NODE_HPP
#define RBTREE_NODE_HPP

#include "utility/pair.hpp"

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

		rbtree_node_base() : _parent(NULL), _left(NULL), _right(NULL), _color(BLACK){}
		rbtree_node_base(rbtree_node_base* parent_ptr, rbtree_node_base* child_ptr)
			: _parent(parent_ptr)
			, _left(child_ptr)
			, _right(child_ptr)
			, _color(RED)
			{}
	};

	//Here, we pass the derived class Node<Val> as a template argument to its own base (Node_base).
	// That allows Node_base to use Node<Val> in its interfaces without even knowing its real name!
	template <typename Value>
	struct rbtree_node_for_map : public rbtree_node_base
	{
		Value 	_value;
		typedef typename Value::first_type key_type;
		explicit rbtree_node_for_map(rbtree_node_base *parent_ptr, rbtree_node_base* child_ptr, const Value &value)
			: rbtree_node_base(parent_ptr, child_ptr), _value(value) {}

		static const key_type& get_key_from_value(const Value& _value) // it will be accessible in rbtree as well for insert() for example
		{
			return _value.first;
		}
		const key_type& get_key() const
		{
			return _value.first;
		}
	};

	template <typename Value>
	struct rbtree_node_for_set : public rbtree_node_base
	{
		Value 	_value;
		typedef Value key_type;

		explicit rbtree_node_for_set(rbtree_node_base *parent_ptr, rbtree_node_base *child_ptr, const Value &value)
			: rbtree_node_base(parent_ptr, child_ptr), _value(value) {}

		static const key_type& get_key_from_value(const Value& _value) // it will be accessible in rbtree as well for insert() for example
		{
			return _value;
		}
		const key_type& get_key() const
		{
			return _value;
		}
	};
}

#endif
