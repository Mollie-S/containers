#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "../utility/reverse_iterator.hpp"

#include "rbtree_iterator.hpp"
#include "rbtree_node.hpp"

namespace ft
{
	template <typename T, typename Compare, typename Alloc, typename Node>
	class rbtree
	{
	public:
        typedef T																						value_type;
		typedef typename Node::key_type 																key_type;
		typedef Compare 																				key_compare;
		typedef Alloc																					allocator_type;
		typedef rbtree_iter<value_type, rbtree_node_base, Node >                   						iterator;
		typedef rbtree_iter<const value_type, const rbtree_node_base, const Node >						const_iterator;
		typedef ft::reverse_iterator<iterator>          												reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>    												const_reverse_iterator;
		typedef typename allocator_type::size_type														size_type;
	private:
		// explanation for rebind: 
		// The _Alloc template is used to obtain objects of some type. The container may have an internal need to allocate objects of a different type. For example, when you have a std::list<T, A>, the allocator A is meant to allocate objects of type T but the std::list<T, A> actually needs to allocate objects of some node type. Calling the node type _Ty, the std::list<T, A> needs to get hold of an allocator for _Ty objects which is using the allocation mechanism provided by A. Using
		// typename _A::template rebind<_Ty>::other
		// specifies the corresponding type. Now, there are a few syntactic annoyances in this declaration:
		// Since rebind is a member template of _A and _A is a template argument, the rebind becomes a dependent name. To indicate that a dependent name is a template, it needs to be prefixed by template. Without the template keyword the < would be considered to be the less-than operator.
		// The name other also depends on a template argument, i.e., it is also a dependent name. To indicate that a dependent name is a type, the typename keyword is needed.
		typedef typename Alloc::template rebind<Node >::other							node_alloc_type;
		typedef typename Alloc::template rebind<ft::rbtree_node_base>::other			node_base_alloc_type;
		typedef Node*																	node_pointer;

		// we will be using _sentinel as a dummy for node leaves pointing to nil. 
		//In order to save a marginal amount of execution time, 
		//these (possibly many) NIL leaves may be implemented as pointers to one unique (and black)
		// sentinel node (instead of pointers of value NULL). view Thomas H. Cormen introduction to algorithms:

		allocator_type 			_alloc;
		node_alloc_type 		_node_alloc;
		node_base_alloc_type	_node_base_alloc;
		size_type       		_size;
		key_compare				_compare;
		rbtree_node_base*		_sentinel;
		rbtree_node_base*		_root;

	public:
		rbtree(const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
			: _size(0)
			, _alloc(alloc)
			, _node_alloc(alloc)
			, _node_base_alloc(alloc)
			, _compare(comp)
			{
				_sentinel = create_sentinel_node();
				_root = _sentinel;
			}

		rbtree(const rbtree& other)
			: _size(0)
			, _alloc(other._alloc)
			, _node_alloc(other._alloc)
			, _node_base_alloc(other._alloc)
			, _compare(other._compare)
		{
			_sentinel = create_sentinel_node();
			_root = _sentinel;
		}

		~rbtree()
		{
			clear();
			destroy_sentinel_node();
		}

		rbtree& operator=(const rbtree& x)
		{
			if (this != &x)
			{
				if (!empty())
				{
					clear();
					destroy_sentinel_node();
				}
				_node_base_alloc = x._node_base_alloc;
				_node_alloc = x._node_alloc;
				_sentinel = create_sentinel_node();
				_root = _sentinel;
				insert(x.begin(), x.end());
			}
			return *this;
		}

	private:
		struct rbtree_iterator_accessor : public iterator 
		{
			inline rbtree_node_base* get_node() const
			{
				return this->_node_ptr;
			}
		};
	
		inline rbtree_node_base* get_node(const iterator& it) const
		{
			return static_cast<const rbtree_iterator_accessor&>(it).get_node();
		}

	public:
		allocator_type get_allocator() const
		{
			return _alloc;
		}

		iterator begin()
		{
			if (empty())
			{
				return end();
			}
			rbtree_node_base *node = rbtree_min(_root);
			return iterator(node);
		}

		// ITERATORS:
		const_iterator begin() const
		{
			if (empty())
			{
				return const_iterator(_root);
			}
			rbtree_node_base *node = rbtree_min(_root);
			return const_iterator(node);
		}

		iterator end()
		{
			return iterator(_sentinel);		
		}

		const_iterator end() const
		{
			return const_iterator(_sentinel);
		}

		reverse_iterator rbegin()
		{
			if (empty())
			{
				return rend();
			}
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const
		{
			if (empty())
			{
				return rend();
			}
			return const_reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());		
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		// CAPACITY:
		bool empty() const
		{
			return (_root == _sentinel);
		}
		size_type max_size() const
		{
			return _node_alloc.max_size();
		}
		size_type size() const
		{
			return _size;
		}

		// MODIFIERS:
		void clear()
		{
			iterator start = begin();
			while (get_node(start) != _sentinel) // pseude_call - inline function
			{
				// need to save the next iterator for the next loop before deleting the node as we're destroying without rebalancing
				rbtree_node_base* node = get_node(start);
				start++;
				delete_node_pointer(node, false);
				_node_alloc.destroy(static_cast<node_pointer>(node));
				_node_alloc.deallocate(static_cast<node_pointer>(node), 1);
			}
			_size = 0;
		}

		void erase(iterator position)
		{
			rbtree_node_base* node_ptr = get_node(position);
			delete_node_pointer(node_ptr,true);
			_node_alloc.destroy(static_cast<node_pointer>(node_ptr));
			_node_alloc.deallocate(static_cast<node_pointer>(node_ptr), 1);
			_size--;
		}
		// can be implemented with found or equal range. Found also calls 2 functions inside it so the complaxity might be equal;
		size_type erase(const key_type& key)
		{
			iterator iter = find(key);
			if (iter == end())
				return 0;
			erase(iter);
			return 1;
		}

		void erase(iterator first, iterator last)
		{
			if (first == begin() && last == end())
			{
				clear(); // we will be deleting all nodes without tree rebalancing after each deletion. saves execution time
			}
			else
			{
				iterator iter = first;
				iterator next = iter;
				while (iter != last)
				{
					next++;
					erase(iter);
					iter = next;
				}
			}
		}

		// insert():
		// single element (1)	
		pair<iterator,bool> insert(const value_type& val)
		{
			pair<rbtree_node_base *, bool> position_pair;
			position_pair = get_position_for_insertion(val);
			if (position_pair.second != false) // if the key didn't exist before and the new node has been inserted
			{
				pair<rbtree_node_base *, bool> insert_pair;
				insert_pair = insert_node_at_position(position_pair, val);
				rbtree_insert_fixup(insert_pair.first);
				return insert_pair;
			}
			return position_pair;
		}

		// with hint (2)
		iterator insert (iterator, const value_type& val)
		{
			return insert(val).first;
		}

		// range (3)
		template <class InputIterator>
		void insert(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
		{
			for (InputIterator iter = first; iter != last; ++iter)
			{
				insert(*iter);
			}
		}

		//LOOKUP:
		size_type count(const key_type& key) const
		{
			if (find(key) == end())
				return (0);
			return (1);
		}

		//The range is defined by two iterators,
		// one pointing to the first element that is not less than key 
		//and another pointing to the first element greater than key. 
		//Alternatively, the first iterator may be obtained with lower_bound(), and the second with upper_bound().
		pair<iterator,iterator> equal_range(const key_type& key)
		{
			return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
		}

		pair<const_iterator,const_iterator> equal_range(const key_type& key) const
		{
			return ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
		}

		iterator find(const key_type& key )
		{
			iterator iter = lower_bound(key);
			if (iter != end() && !_compare(key,	Node::get_key_from_value(*iter)))
				return iter;
			return end();
		}

		const_iterator find(const key_type& key) const
		{
			const_iterator iter = lower_bound(key);		
			if (iter != end() && !_compare(key, Node::get_key_from_value(*iter)))
				return iter;
			return end();
		}
		
		//A similar member function, upper_bound, has the same behavior as lower_bound,
		// except in the case that the map contains an element with a key equivalent to k:
		// In this case, lower_bound returns an iterator pointing to that element,
		// whereas upper_bound returns an iterator pointing to the next element.
		iterator lower_bound(const key_type& key)
		{
			rbtree_node_base* node_ptr = _root;
			rbtree_node_base* node_with_lower_value = _sentinel;
			while (node_ptr != _sentinel)
			{
				if (_compare(static_cast<node_pointer>(node_ptr)->get_key(), key))
				{
					node_ptr = node_ptr->_right;
				}
				else
				{
					node_with_lower_value = node_ptr;
					node_ptr = node_ptr->_left;
				}
			}
			return iterator(node_with_lower_value);
		}
		
		const_iterator lower_bound(const key_type& key) const
		{
			rbtree_node_base* node_ptr = _root;
			rbtree_node_base* node_with_lower_value = _sentinel;
			while (node_ptr != _sentinel)
			{
				if (_compare(static_cast<node_pointer>(node_ptr)->get_key(), key))
				{
					node_ptr = node_ptr->_right;
				}
				else
				{
					node_with_lower_value = node_ptr;
					node_ptr = node_ptr->_left;
				}
			}
			return const_iterator(node_with_lower_value);
		}
		
		// returns the iterator pointing to the element > than the key
		iterator upper_bound (const key_type& key)
		{
			rbtree_node_base* node_ptr = _root;
			rbtree_node_base* larger = _sentinel;
			while (node_ptr != _sentinel)
			{
				if (_compare(key, static_cast<node_pointer>(node_ptr)->get_key()))
				{
					larger = node_ptr;
					node_ptr = node_ptr->_left;
				}
				else
					node_ptr = node_ptr->_right;
			}
			return iterator(larger);
		}
		
		const_iterator upper_bound (const key_type& key) const
		{
			rbtree_node_base* node_ptr = _root;
			rbtree_node_base* equal_or_higher = _root;
			while (node_ptr != _sentinel)
			{
				if (_compare(key, static_cast<node_pointer>(node_ptr)->get_key()))
				{
					equal_or_higher = node_ptr;
					node_ptr = node_ptr->_left;
				}
				else
					node_ptr = node_ptr->_right;
			}
			return const_iterator(equal_or_higher);
		}
		
		// OBSERVERS:
		key_compare key_comp() const
		{
			return _compare;
		}

		void swap(rbtree& other )
		{
			ft::swap(other._sentinel, _sentinel);
            ft::swap(other._root, _root);
            ft::swap(other._size, _size);
            ft::swap(other._alloc, _alloc);
            ft::swap(other._node_alloc, _node_alloc);
            ft::swap(other._compare, _compare);
		}

// 		// TODO: tree print helper must be commented out
// 		void tree_print_helper()
// 		{
// 			iterator f_it = begin();
// 			iterator itEnd = end();
// 			int n = 1;
// 			for (iterator i = f_it; i != itEnd; ++i, ++n)
// 			{
// 				std::string col = "RED  ";
// 				if (get_node(i)->_color == 0)
// 				{
// 					col = "BLACK";
// 				}
// 				std::cout << n << ":           	  -----|" << i->first << " " << col ;
// 				if (get_node(i)->_parent == _sentinel)
// 				{
// 					std::cout << " (parent -  sentinel)|-----   " ;
// 				}
// 				else
// 				{
// 					std::cout << " (parent - " << (get_node(i)->_parent)->_key << ")|-----  ";
// 				}
// 
// 				if (get_node(i) == _root)
// 				{
// 					std::cout << "THIS IS THE ROOT";
// 				}
// 
// 				std::cout << std::endl;
// 				if (get_node(i)->_left == _sentinel)
// 				{
// 					std::cout << "  left - sentinel|\n" ;
// 				}
// 				else
// 				{
// 					std::cout << "  left - " << (get_node(i)->_left)->_key<<  "|\n";
// 				}
// 				if (get_node(i)->_right == _sentinel)
// 				{
// 					std::cout << "  right-  sentinel|\n" ;
// 				}
// 				else
// 				{
// 					std::cout << "  right - " << (get_node(i)->_right)->_key << "|\n";
// 				}
// 
// 				std::cout << std::endl;
// 			}
// 				std::cout <<"--------------------------------------------------"<<  std::endl;
// 		}

	private:
		node_pointer create_node(rbtree_node_base* parent_ptr, rbtree_node_base* child_ptr, const value_type& value)
		{
			node_pointer new_node = _node_alloc.allocate(1); //Atsuccessorts to allocate a block of storage with a size large enough to contain n elements of member type value_type (an alias of the allocator's template parameter), and returns a pointer to the first element.
			_node_alloc.construct(new_node, parent_ptr, child_ptr, value);
			return new_node;
		}

		pair<rbtree_node_base*, bool> get_position_for_insertion(const value_type& value)
		{
			bool isUniqueKey = true;
			rbtree_node_base* position = _sentinel;
			rbtree_node_base* current = _root;
			const key_type key = Node::get_key_from_value(value);
			while(current != _sentinel)
			{
				position = current;
				if (key == static_cast<node_pointer>(current)->get_key())
				{
					isUniqueKey = false;
					return ft::pair<rbtree_node_base*, bool>(current, isUniqueKey);
				}
				if (_compare(key, static_cast<node_pointer>(current)->get_key()))
				{
					current = current->_left;
				} 
				else{
					current = current->_right;
				}
			}
			return ft::pair<rbtree_node_base *, bool>(position, isUniqueKey);
		}

		pair<rbtree_node_base*, bool> insert_node_at_position(ft::pair<rbtree_node_base *, bool> position_pair,
														const value_type& value)
		{
			rbtree_node_base *position = position_pair.first;
			rbtree_node_base *new_node = create_node(position, _sentinel, value);
			const key_type key = Node::get_key_from_value(value);
			if (position == _sentinel)
			{
				_root = new_node;
				_root->_parent = _sentinel;
				_root->_color = BLACK;
				_sentinel->_parent = _root;
			}
			else if (_compare(key, static_cast<node_pointer>(position)->get_key()))
			{
				position->_left = new_node;
			}
			else
			{
				position->_right = new_node;
			}
			_size++;
			return ft::pair<rbtree_node_base *, bool>(new_node, position_pair.second);
		}

		void assign_subnode_to_new_parent(rbtree_node_base* node, rbtree_node_base* subnode)
		{
			if (node->_parent == _sentinel)
			{
				_root = subnode;
				_sentinel->_parent = _root;
			}
			else if (node == node->_parent->_left)
			{
				node->_parent->_left = subnode; // left child of the node's parent points to the subnode now
			}
			else
			{
				node->_parent->_right = subnode; // or the right child of the node's parent points to the subnode now
			}
		}

		// we're rotating left so that the right_subnode(right child) of the node becomes the parent of the current node
		// current node will become the left child of te current subnode
		// and left child of the subnode becomes the right child of the current node
		void rotate_left(rbtree_node_base* node)
		{
			rbtree_node_base* subnode = node->_right;
			node->_right = subnode->_left;
			if (subnode->_left != _sentinel)
			{
				subnode->_left->_parent = node; //linking left child of the subnode to the node
			}
			subnode->_parent = node->_parent; //linking node's parent to the subnode
			assign_subnode_to_new_parent(node, subnode);
			subnode->_left = node;
			node->_parent = subnode;
		}

		void rotate_right(rbtree_node_base* node)
		{
			rbtree_node_base* subnode = node->_left;
			node->_left = subnode->_right;
			if (subnode->_right != _sentinel)
			{
				subnode->_right->_parent = node; //linking left child of the subnode to the node
			}
			subnode->_parent = node->_parent; //linking node's parent to the subnode
			assign_subnode_to_new_parent(node, subnode);
			subnode->_right = node;
			node->_parent = subnode;
		}

		rbtree_node_base* recolor_grandparent_and_children(rbtree_node_base* grandparent)
		{
			grandparent->_left->_color = BLACK;
			grandparent->_right->_color = BLACK;
			grandparent->_color = RED;
			return grandparent;
		}

		void swap_colors(rbtree_node_base* node, rbtree_node_base* parent)
		{
			node->_color = BLACK;
			parent->_color = RED;
		}

		void rbtree_insert_fixup_right(rbtree_node_base* node, rbtree_node_base* grandparent)
		{
			rbtree_node_base* uncle = grandparent->_left;
			if (uncle->_color == RED)
			{
				node = recolor_grandparent_and_children(grandparent);
			}
			else 
			{
				if (node == node->_parent->_left)
				{
					node = node->_parent;
					rotate_right(node);
				}
				swap_colors(node->_parent, node->_parent->_parent);
				rotate_left(node->_parent->_parent);
			}
		}

		void rbtree_insert_fixup_left(rbtree_node_base* node, rbtree_node_base* grandparent)
		{
			rbtree_node_base *uncle = grandparent->_right;
			if (uncle->_color == RED)
			{
				node = recolor_grandparent_and_children(grandparent);
			}
			else 
			{
				if (node == node->_parent->_right)
				{
					node = node->_parent;
					rotate_left(node);
				}
					swap_colors(node->_parent, node->_parent->_parent);
				rotate_right(node->_parent->_parent);
			}
		}

		void rbtree_insert_fixup(rbtree_node_base* node)
		{
			while (node->_parent->_color == RED)
			{
				rbtree_node_base* grandparent = node->_parent->_parent;
				if (node->_parent == grandparent->_left)
				{
					rbtree_insert_fixup_left(node, grandparent);
				}
				else
				{
					rbtree_insert_fixup_right(node, grandparent);
				}
			}
			_root->_color = BLACK;
		}

		pair<rbtree_node_base*, rbtree_node_base*> delete_node_with_null_child(rbtree_node_base* node_to_delete)
		{
			rbtree_node_base* replacement;
			if (node_to_delete->_left == _sentinel)
			{
				replacement = node_to_delete->_right;
				rb_transplant(node_to_delete, replacement);
			}
			else if (node_to_delete->_right == _sentinel)
			{
				replacement = node_to_delete->_left;
				rb_transplant(node_to_delete, replacement);
			}
			rbtree_node_base* replacement_parent = node_to_delete->_parent;
			return ft::make_pair(replacement, replacement_parent);
		}

		pair<rbtree_node_base*, rbtree_node_base*>  delete_node_with_two_children(rbtree_node_base* node_to_delete, rbtree_node_base* successor)
		{
			rbtree_node_base *replacement;
			replacement = successor->_right;
			rbtree_node_base* replacement_parent = successor->_parent;
			if (successor->_parent == node_to_delete)
			{
				if (replacement != _sentinel)
					replacement->_parent = successor;
				replacement_parent = successor;
			}
			else
			{
				rb_transplant(successor, replacement);
				successor->_right = node_to_delete->_right;
				successor->_right->_parent = successor;
			}
			rb_transplant(node_to_delete, successor);
			successor->_left = node_to_delete->_left;
			successor->_left->_parent = successor;
			successor->_color = node_to_delete->_color;
			return ft::make_pair(replacement, replacement_parent);
		}

	// replaces pointer of the node to delete with the pointer to the replacing node
		void rb_transplant(rbtree_node_base* node, rbtree_node_base* replacement)
		{
			if (node->_parent == _sentinel)
			{
				_root = replacement;
				_sentinel->_parent = _root;
			}
			else if (node == node->_parent->_left)
			{
				node->_parent->_left = replacement;
			}
			else
			{
				node->_parent->_right = replacement;
			}
			if (replacement != _sentinel)
			{
				replacement->_parent = node->_parent;
			}
		}

	// replacing pair will hold the pointer to the replacing node and its parent
	// (parent is needed for the case the replacement is sentinel and its parent pointing to the root)
			void delete_node_pointer(rbtree_node_base* node_to_delete, bool fixup) // bool fixup(true) marks when the functtion is called not from clear()
			{
				pair<rbtree_node_base*, rbtree_node_base*> replacing_pair;
				int original_color = node_to_delete->_color;
				if (node_to_delete->_left == _sentinel
					|| node_to_delete->_right == _sentinel)
				{
					replacing_pair = delete_node_with_null_child(node_to_delete);
				}
				else
				{
					rbtree_node_base* successor;
					successor = rbtree_min(node_to_delete->_right); 
					original_color = successor->_color;
					replacing_pair = delete_node_with_two_children(node_to_delete, successor);
				}
				if (fixup && original_color == BLACK)
				{
					rbtree_delete_fixup(replacing_pair);
				}
			}

		pair<rbtree_node_base*, rbtree_node_base*> rbtree_delete_fixup_right(pair<rbtree_node_base*, rbtree_node_base*> replacing_pair)
		{
			rbtree_node_base* node = replacing_pair.first;
			rbtree_node_base* parent = replacing_pair.second;
			rbtree_node_base* sibling;
			sibling = parent->_left;
			if (sibling->_color == RED)
			{
				swap_colors(sibling, parent);
				rotate_right(parent);
				sibling = parent->_left;
			}
			if (sibling == _sentinel)
				return make_pair(_sentinel, _sentinel);
			if (sibling->_left->_color == BLACK 
			&& sibling->_right->_color == BLACK)
			{
				sibling->_color = RED;
				node = parent;
				parent = parent->_parent;
			}
			else
			{
				if (sibling->_left->_color == BLACK)
				{
					swap_colors(sibling->_right, sibling);
					rotate_left(sibling);
					sibling = parent->_left;
				}
				sibling->_color = parent->_color;
				parent->_color = BLACK;
				sibling->_right->_color = BLACK;
				rotate_right(parent);
				node = _root;
				parent = _root->_parent;
			}
			return make_pair(node, parent);
		}

		pair<rbtree_node_base*, rbtree_node_base*> rbtree_delete_fixup_left(pair<rbtree_node_base*, rbtree_node_base*> replacing_pair)
		{
			rbtree_node_base *node = replacing_pair.first;
			rbtree_node_base *parent = replacing_pair.second;
			rbtree_node_base *sibling;
			sibling = parent->_right;
			if (sibling->_color == RED)
			{
				swap_colors(sibling, parent);
				rotate_left(parent);
				sibling = parent->_right;
			}
			if (sibling->_left->_color == BLACK 
			&& sibling->_right->_color == BLACK)
			{
				sibling->_color = RED;
				node = parent;
				parent = parent->_parent;
			}
			else 
			{
				if (sibling->_right->_color == BLACK)
				{
					swap_colors(sibling->_left, sibling);
					rotate_right(sibling);
					sibling = parent->_right;
				}
				sibling->_color = parent->_color;
				parent->_color = BLACK;
				sibling->_right->_color = BLACK;
				rotate_left(parent);
				node = _root;
				parent = _root->_parent;
			}
			return make_pair(node, parent);
		}

		// replacing_pair.first  == the node
		// replacing_pair.second == node's parent
		void rbtree_delete_fixup(pair<rbtree_node_base*, rbtree_node_base*> replacing_pair)
		{
			while (replacing_pair.first != _root && replacing_pair.first->_color == BLACK)
			{
				if (replacing_pair.second == _sentinel || replacing_pair.second->_left == _sentinel && replacing_pair.second->_right == _sentinel)
				{
					break;
				}
				if (replacing_pair.first == replacing_pair.second->_left)
				{
					replacing_pair = rbtree_delete_fixup_left(replacing_pair);
				}
				else
				{
					replacing_pair = rbtree_delete_fixup_right(replacing_pair);
				}
			}
			replacing_pair.first->_color = BLACK;
		}

		rbtree_node_base* rbtree_min(rbtree_node_base* node) const
		{
			while (node->_left != _sentinel) // iterating until the left is pointing to the NIL that is the sentinel node
			{
				node = node->_left;
			}
			return node;
		}

		rbtree_node_base* create_sentinel_node()
		{
			rbtree_node_base* null_base_node = _node_base_alloc.allocate(1);
			_node_base_alloc.construct(null_base_node);
			return null_base_node;
		}

		void destroy_sentinel_node()
		{
			_node_base_alloc.destroy(_sentinel);
			_node_base_alloc.deallocate(_sentinel, 1);
		}
	};

}

#endif
