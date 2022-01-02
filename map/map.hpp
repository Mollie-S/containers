#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <stddef.h>
#include <stdbool.h>
#include <iostream>
#include "rbtree_node.hpp"
#include "map_iterator.hpp"


namespace ft
{
	template < class Key,                                     		// map::key_type
           class T,                                       			// map::mapped_type
           class Compare = ::std::less<Key>,                     	// map::key_compare
           class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
           >
    class map {
    public:

        typedef Key											key_type;
        typedef T											mapped_type;
        typedef ft::pair<const key_type, mapped_type>		value_type;
        typedef Compare										key_compare;
        typedef Alloc										allocator_type;
        typedef value_type&									reference;
        typedef const value_type&							const_reference;
		typedef typename allocator_type::pointer        	pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;

	private:
		typedef typename Alloc::template rebind<ft::rbtree_node<value_type> >::other node_alloc_type;

	public:
		typedef map_iter<value_type, rbtree_node_base*, rbtree_node<value_type>* >                   		iterator;
		typedef map_iter<value_type, const rbtree_node_base*, const rbtree_node<value_type>* >              const_iterator;


		// TODO: reverse iterator
		// typedef reverse_iterator<iterator>               reverse_iterator;
		// typedef reverse_iterator<const_iterator>         const_reverse_iterator;


		// static_assert(sizeof(__diagnose_non_const_comparator<_Key, _Compare>()), "");
		// static_assert((is_same<typename allocator_type::value_type, value_type>::value),
		// 			"Allocator::value_type must be same type as value_type");


		class value_compare // Nested function class to compare elements
			: public ::std::binary_function<value_type, value_type, bool> { //  // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
			friend class map;
		protected:
			Compare comp; // Notice that value_compare has no public constructor, therefore no objects can be directly created from this nested class outside map members.
			value_compare(Compare c) : comp(c) {} // // constructed with map's comparison object
		public:
			typedef bool result_type;
  			typedef value_type first_argument_type;
  			typedef value_type second_argument_type;
  			bool operator()(const value_type& x, const value_type& y) const {
				return comp(x.first, y.first);
			}
		};

	private:
		typedef ft::rbtree_node<value_type>*	node_pointer;

		// explanation for rebind: 
		// The _Alloc template is used to obtain objects of some type. The container may have an internal need to allocate objects of a different type. For example, when you have a std::list<T, A>, the allocator A is meant to allocate objects of type T but the std::list<T, A> actually needs to allocate objects of some node type. Calling the node type _Ty, the std::list<T, A> needs to get hold of an allocator for _Ty objects which is using the allocation mechanism provided by A. Using
		// typename _A::template rebind<_Ty>::other
		// specifies the corresponding type. Now, there are a few syntactic annoyances in this declaration:
		// Since rebind is a member template of _A and _A is a template argument, the rebind becomes a dependent name. To indicate that a dependent name is a template, it needs to be prefixed by template. Without the template keyword the < would be considered to be the less-than operator.
		// The name other also depends on a template argument, i.e., it is also a dependent name. To indicate that a dependent name is a type, the typename keyword is needed.

		// we will be using _sentinel as a dummy for node leaves pointing to nil. 
		//In order to save a marginal amount of execution time, 
		//these (possibly many) NIL leaves may be implemented as pointers to one unique (and black)
		// sentinel node (instead of pointers of value NULL). view Thomas H. Cormen introduction to algorithms:
		rbtree_node_base 	_sentinel;
		rbtree_node_base*	_root;
		allocator_type 		_alloc;
		node_alloc_type		_node_alloc;
		size_type       	_size;
		key_compare			_compare;
	
	private:
		node_pointer create_node(rbtree_node_base* parent_ptr, rbtree_node_base* child_ptr, const value_type& value)
		{
			node_pointer new_node = _node_alloc.allocate(1); //Atsuccessorts to allocate a block of storage with a size large enough to contain n elements of member type value_type (an alias of the allocator's template parameter), and returns a pointer to the first element.
			_node_alloc.construct(new_node, parent_ptr, child_ptr, value);
			return new_node;
		}

		pair<rbtree_node_base*, bool> insert_node_at_position(const value_type& value)
		{
			bool isUniqueKey = true;
			rbtree_node_base* position = &_sentinel;
			rbtree_node_base* current = _root;
			const key_type key = value.first;
			while(current != &_sentinel)
			{
				position = current;
				if (key == static_cast<node_pointer>(current)->_value.first){
					isUniqueKey = false;
					return ft::pair<rbtree_node_base *, bool>(current, isUniqueKey);
				}
				if (_compare(key, static_cast<node_pointer>(current)->_value.first))
				{
					current = current->_left;
				} 
				else{
					current = current->_right;
				}
			}
			rbtree_node_base* new_node = create_node(position, &_sentinel, value);
			if (position == &_sentinel)
			{
				_root = new_node;
				_root->_parent = &_sentinel;
				_root->_color = BLACK;
				_sentinel._parent = _root;
			}
			else if (_compare(key, static_cast<node_pointer>(position)->_value.first))
			{
				position->_left = new_node;
			}
			else
			{
				position->_right = new_node;
			}
			_size++;
			return ft::pair<rbtree_node_base *, bool>(new_node, isUniqueKey);
		}

		void rotate_left(rbtree_node_base* node)
		{
			rbtree_node_base* temp = node->_right;
			node->_right = temp->_left;
			if (temp->_left != &_sentinel)
			{
				temp->_left->_parent = node; //linking left child of the temp to the node
			}
			temp->_parent = node->_parent; //linking node's parent to the temp
			if (node->_parent == &_sentinel)
			{
				_root = temp;
				_sentinel._parent = _root;
			}
			else if (node == node->_parent->_left)
			{
				node->_parent->_left = temp; // left child of the node's parent points to the temp now
			}
			else
			{
				node->_parent->_right = temp; // or the right child of the node's parent points to the temp now
			}
			temp->_left = node;
			node->_parent = temp;
		}

		void rotate_right(rbtree_node_base* node)
		{
			rbtree_node_base* temp = node->_left;
			node->_left = temp->_right;
			if (temp->_right != &_sentinel)
			{
				temp->_right->_parent = node; //linking left child of the temp to the node
			}
			temp->_parent = node->_parent; //linking node's parent to the temp
			if (node->_parent == &_sentinel)
			{
				_root = temp;
				_sentinel._parent = _root;
			}
			else if (node == node->_parent->_left)
			{
				node->_parent->_left = temp; // left child of the node's parent points to the temp now
			}
			else
			{
				node->_parent->_right = temp; // or the right child of the node's parent points to the temp now
			}
			temp->_right = node;
			node->_parent = temp;
		}

		rbtree_node_base* recolor_grandparent_and_children(rbtree_node_base* grandparent)
		{
			grandparent->_left->_color = BLACK;
			grandparent->_right->_color = BLACK;
			grandparent->_color = RED;
			return grandparent;
		}

		void recolor_node_and_parent(rbtree_node_base* node, rbtree_node_base* parent)
		{
			node->_color = BLACK;
			parent->_color = RED;
		}

		void rbtree_insert_fixup(rbtree_node_base* node)
		{
			while (node->_parent->_color == RED)
			{
				rbtree_node_base* parent = node->_parent;
				rbtree_node_base* grandparent = parent->_parent;
				if (parent == grandparent->_left)
				{
					rbtree_node_base* uncle = grandparent->_right;
					if (uncle->_color == RED)
					{
						node = recolor_grandparent_and_children(grandparent);
					}
					else 
					{
						if (node == parent->_right)
						{
							node = node->_parent;
							rotate_left(node);
						}
							recolor_node_and_parent(node->_parent, node->_parent->_parent);
						rotate_right(node->_parent->_parent);
					}
				}
				else
				{
					rbtree_node_base* uncle = grandparent->_left;
					if (uncle->_color == RED)
					{
						node = recolor_grandparent_and_children(grandparent);
					}
					else 
					{
						if (node == parent->_left)
						{
							node = node->_parent;
							rotate_right(node);
						}
						recolor_node_and_parent(node->_parent, node->_parent->_parent);
						rotate_left(node->_parent->_parent);
					}
				}
			}
			_root->_color = BLACK;
		}

public:
		// // TODO:
		// // CONSTRUCTORS:
		// //empty (1)
		// _alloc(alloc), _node_alloc(alloc): allocator has got a template constructor that allows to construct an instance out of another type
		explicit map (const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type())
					 : _sentinel(NULL,NULL)
					 , _root(&_sentinel)
					 , _size(0)
					 , _alloc(alloc)
					 , _node_alloc(alloc)
					 , _compare(comp)
					 {
						_sentinel._color = BLACK;
					 }

		// // range (2)
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
			 		: _sentinel(NULL,NULL)
					 , _root(&_sentinel)
					 , _size(0)
					 , _alloc(alloc)
					 , _node_alloc(alloc)
					 , _compare(comp)
					 {
						_sentinel._color = BLACK;
						for (InputIterator iter = first; iter != last; ++iter)
						{
							insert(*iter);
						}
					 }
					 //TODO: copy constructor:
		// // copy (3)
		// map (const map& x);

		 //TODO: operaotor=
		// map& operator=(const map& x)
		// {
		// 	
		// }

		allocator_type get_allocator() const
		{
			return _alloc;
		}
		
// 		//TODO:
// 		// ELEMENT ACCESS:
// 		mapped_type& operator[] (const key_type& k)
// 		{
// 
// 		}

		// ITERATORS:
	private:
		rbtree_node_base* rbtree_min(rbtree_node_base* node)
		{
			while (node->_left != &_sentinel) // iterating until the left are not pointing to the NIL that is the sentinel node
			{
				node = node->_left;
			}
			return node;
		}
	public:
		iterator begin()
		{
			if (empty())
				return iterator(_root);
			rbtree_node_base *node = rbtree_min(_root);
			return iterator(node);
		}
		
		const_iterator begin() const
		{
			if (empty())
				return const_iterator(_root);
			rbtree_node_base *node = rbtree_min(_root);
			return const_iterator(node);
		}
		iterator end()
		{
			return iterator(&_sentinel);		
		}
		const_iterator end() const
		{
			return const_iterator(&_sentinel);
		}

		// CAPACITY:

		bool empty() const
		{
			return (_root == &_sentinel);
		}
		size_type max_size() const
		{
			return _node_alloc.max_size();
		}
		size_type size() const
		{
			return _size;
		}

		// // MODIFIERS:
		// TODO; CLEAR
// 		void clear()
// 		{
// 
// 		}

	private:

	// replaces pointer of the node to delete with the pointer to the replacing node
		void rb_transplant(rbtree_node_base* node_to_delete, rbtree_node_base* replacing_node)
		{
			if (node_to_delete->_parent == &_sentinel)
			{
				_root = replacing_node;
			}
			else if (node_to_delete == node_to_delete->_parent->_left)
			{
				node_to_delete->_parent->_left = replacing_node;
			}
			else
			{
				node_to_delete->_parent->_right = replacing_node;
			}
			replacing_node->_parent = node_to_delete->_parent;
		}

		void delete_node_pointer(rbtree_node_base* node_to_delete)
		{
			rbtree_node_base* successor = node_to_delete;
			rbtree_node_base* node_to_transplant;
			int successor_original_color = successor->_color;
			if (node_to_delete->_left == &_sentinel)
			{
				node_to_transplant = node_to_delete->_right;
				rb_transplant(node_to_delete, node_to_delete->_right);
			}
			else if (node_to_delete->_right == &_sentinel)
			{
				node_to_transplant = node_to_delete->_left;
				rb_transplant(node_to_delete, node_to_delete->_left);
			}
			else
			{
				successor = rbtree_min(node_to_delete->_right); //  successor must be the node in that subtree with the smallest key; hence the call to tree_min
				successor_original_color = successor->_color;
				node_to_transplant = successor->_right;
				if (successor->_parent == node_to_delete)
				{
					node_to_transplant->_parent = successor;
				}
				else
				{
					rb_transplant(successor, node_to_transplant);
					successor->_right = node_to_delete->_right;
					successor->_right->_parent = successor;
				}
				rb_transplant(node_to_delete, successor);
				successor->_left = node_to_delete->_left;
				successor->_left->_parent = successor;
				successor->_color = node_to_delete->_color;
				if (successor_original_color == BLACK)
				{
					rbtree_delete_fixup(node_to_transplant);
				}
			}
		}

		void rbtree_delete_fixup(rbtree_node_base* node)
		{
			while (node != _root && node->_color == BLACK)
			{
				rbtree_node_base* sibling;
				if (node == node->_parent->_left)
				{
					sibling = node->_parent->_right;
					if (sibling->_color == RED)
					{
						recolor_node_and_parent(sibling, node->_parent);
						rotate_left(node->_parent);
						sibling = node->_parent->_right;
					}
					if (sibling->_left->_color == BLACK && sibling->_right->_color == BLACK)
					{
						sibling->_color = RED;
						node = node->_parent;
					}
					else 
					{
						if (sibling->_right->_color == BLACK)
						{
							recolor_node_and_parent(sibling->_left, sibling);
							rotate_right(sibling);
							sibling = node->_parent->_right;
						}
						sibling->_color = node->_parent->_color;
						node->_parent->_color = BLACK;
						sibling->_right->_color = BLACK;
						rotate_left(node->_parent);
						node = _root;
					}
				}
				else
				{
					sibling = node->_parent->_left;
					if (sibling->_color == RED)
					{
						recolor_node_and_parent(sibling, node->_parent);
						rotate_right(node->_parent);
						sibling = node->_parent->_left;
					}
					if (sibling->_left->_color == BLACK && sibling->_right->_color == BLACK)
					{
						sibling->_color = RED;
						node = node->_parent;
					}
					else
					{
						if (sibling->_left->_color == BLACK)
						{
							recolor_node_and_parent(sibling->_right, sibling);
							rotate_left(sibling);
							sibling = node->_parent->_left;
						}
						sibling->_color = node->_parent->_color;
						node->_parent->_color = BLACK;
						sibling->_right->_color = BLACK;
						rotate_right(node->_parent);
						node = _root;
					}
				}
			}
			node->_color = BLACK;
		}

	public:

		void erase(iterator position)
		{
			rbtree_node_base* node_ptr = position.get_node_pointer();
			delete_node_pointer(node_ptr);
			_node_alloc.destroy(static_cast<node_pointer>(node_ptr));
			_node_alloc.deallocate(static_cast<node_pointer>(node_ptr), 1);
			_size--;
		}

		// size_type erase (const key_type& k);

		//      void erase (iterator first, iterator last);

		// single element (1)	
		pair<iterator,bool> insert(const value_type& val)
		{
			ft::pair<rbtree_node_base *, bool> i_pair;
			i_pair = insert_node_at_position(val);
			if (i_pair.second != false) // if the key didn't exist before and the new node has been inserted
			{
				rbtree_insert_fixup(i_pair.first);
			}
			return i_pair;
		}
		//TODO: insert
		// // with hint (2)
		// iterator insert (iterator position, const value_type& val);
		// // range (3)
		// template <class InputIterator>
		// void insert (InputIterator first, InputIterator last);

		//LOOKUP:
		size_type count(const key_type& key) const
		{
			if (find(key) == end())
				return (0);
			return (1);
		}
		//TODO:
		// pair<iterator,iterator>             equal_range (const key_type& key);
		// pair<const_iterator,const_iterator> equal_range (const key_type& key) const;

		iterator find(const Key& key )
		{
			iterator iter = lower_bound(key);		
			if (iter != end() && !_compare(key, iter->first))
				return iter;
			return end();
		}
		const_iterator find(const key_type& key) const
		{
			const_iterator iter = lower_bound(key);		
			if (iter != end() && !_compare(key, iter->first))
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
			rbtree_node_base* node_with_lower_value = _root;
			while (node_ptr != &_sentinel)
			{
				if (!_compare(static_cast<node_pointer>(node_ptr)->_value.first, key))
				{
					node_with_lower_value = node_ptr;
					node_ptr = node_ptr->_left;
				}
				else
					node_ptr = node_ptr->_right;
			}
			return iterator(node_with_lower_value);
		}
		const_iterator lower_bound(const key_type& key) const
		{
			rbtree_node_base* node_ptr = _root;
			rbtree_node_base* node_with_lower_value = _root;
			while (node_ptr != &_sentinel)
			{
				if (!_compare(static_cast<node_pointer>(node_ptr)->_value.first, key))
				{
					node_with_lower_value = node_ptr;
					node_ptr = node_ptr->_left;
				}
				else
					node_ptr = node_ptr->_right;
			}
			return const_iterator(node_with_lower_value);
		}
		// returns the iterator pointing to the element > than the key
		iterator upper_bound (const key_type& key)
		{
			rbtree_node_base* node_ptr = _root;
			rbtree_node_base* equal_or_higher = _root;
			while (node_ptr != &_sentinel)
			{
				if (_compare(static_cast<node_pointer>(node_ptr)->_value.first, key))
				{
					equal_or_higher = node_ptr;
					node_ptr = node_ptr->_left;
				}
				else
					node_ptr = node_ptr->_right;
			}
			return iterator(equal_or_higher);
		}
		const_iterator upper_bound (const key_type& key) const
		{
			rbtree_node_base* node_ptr = _root;
			rbtree_node_base* equal_or_higher = _root;
			while (node_ptr != &_sentinel)
			{
				if (_compare(static_cast<node_pointer>(node_ptr)->_value.first, key))
				{
					equal_or_higher = node_ptr;
					node_ptr = node_ptr->_left;
				}
				else
					node_ptr = node_ptr->_right;
			}
			return const_iterator(equal_or_higher);
		}
	};

}

#endif
