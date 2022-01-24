# C++ containers

The goal of the project is to understand how C++ containers work by implementing my's own version that replicates their behavior.
The subject requires the use of **namespace ft** to differentiate the reproduced containers from those available in the standard library.

The following STL containers are implemented:
- Stack
- Vector
- Map
- Set


## Stack

## Vector

## Map and Set

Both are ordered containers holding only unique keys and relying on the Red Black Tree as the data structure for holding their values.
The basic difference between these two containers is that Map contains the data in the key-value pair while Set is storing keys only.
  ### Red Black Tree
A red-black tree is a binary search tree with one extra bit of storage per node: its
color, which can be either RED or BLACK. By constraining the node colors on any
simple path from the root to a leaf, red-black trees ensure that no such path is more
than twice as long as any other, so that the tree is approximately **balanced.**

**The tree satisfies the following red-black properties:**
1. Every node is either red or black.
2. The root is black.
3. Every leaf (NIL) is black.
4. If a node is red, then both its children are black.
5. For each node, all simple paths from the node to descendant leaves contain the
same number of black nodes.

  ![](docs/images/red_black_tree.png)
  
Node holding the key **26** in the picture is the **root** node.

As a matter of convenience in dealing with boundary conditions in red-black
tree code, a single **sentinel** to represent NIL is used.
We use the sentinel so that we can treat a NIL child of a node x as an ordinary
node whose parent is x. Although we instead could add a distinct sentinel node
for each NIL in the tree, so that the parent of each NIL is well defined, that approach would waste space.

Sentinel's parent is always pointing to the root(it is updated if the root is changed) which is helpful for handling the situations
when the iterator returned by **end()** is decremented and dereferenced.
```
ft::map<int, int>::iterator iter = my_map.end();
iter--;
std::cout << "The key is << iter->first << std::endl;
```
The sentinel node doesn't hold a value and is an object of the **rbtree_base** class thus having only _color_, _left_, _right_ and _parent_ attributes.
This structure allows to escape 2 problems: 
- any object constructed from a class without a default constructor can be saved in a Map/Set node;
- no unnecessary additional memory is allocated that can be a problem for a potentially heavily weighted objects;

[Source for the Red Black Tree](https://edutechlearners.com/download/Introduction_to_algorithms-3rd%20Edition.pdf)
