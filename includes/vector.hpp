#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory> //needed for allocator
#include <iostream>
#include <cmath>
#include <iterator> // for std::distance

#include "iterator/vector_iterator.hpp"
#include "iterator/reverse_iterator.hpp"

#include "utility/is_iterator.hpp"
#include "utility/is_integral.hpp"
#include "utility/enable_if.hpp"
#include "utility/lexicographical_compare.hpp"
#include "utility/equal.hpp"
#include "utility/ft_swap.hpp"

namespace ft
{
    template <class T, class Alloc = ::std::allocator<T> > // generic template
    class vector
    {
    public:
     //  iterators are an abstraction of pointers

    //  vector<string>::const_iterator   iter;     // is an iterator that refers to things that are constant, while
    // const vector<string>::iterator   iter;       // would make the iterator itself constant, but allow you to modify the object it refers to.
        		
        typedef T                                       value_type; // cannot use "using as it is c++11"
		typedef Alloc                                   allocator_type;
		typedef value_type&                             reference;
		typedef value_type const &                      const_reference;
		typedef typename allocator_type::pointer        pointer;
		typedef typename allocator_type::const_pointer  const_pointer;
		typedef std::ptrdiff_t                          difference_type;
		typedef size_t                                  size_type;
        typedef vector_iter<value_type>                 iterator;
        typedef vector_iter<const value_type>           const_iterator;
        typedef ft::reverse_iterator<iterator>          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

    private:
        pointer         _elements;     // pointer to the first element of the container
        size_type       _size;       // num of elements in the container
        size_type       _capacity;   // capacity of the container
        allocator_type  _alloc; // the type of the allocator used

    public:
        //default constructor(1):
        explicit vector<T, Alloc>(const allocator_type &alloc = allocator_type())
            : _elements(NULL), _size(0), _capacity(0),  _alloc(alloc) {}
            
        //fill constructor(2)
        explicit vector<T, Alloc>(size_type n, const value_type &val = value_type(),
                                  const allocator_type &alloc = allocator_type())
            : _size(n), _capacity(n), _alloc(alloc)
        {
            _elements = _alloc.allocate(n);
            try
            {
                uninitialized_fill(_elements, _elements + n, val);
            }
            catch (...)
            {
                _alloc.deallocate(_elements, n);
                throw;
            }
        }

        // the standard says that if the range constructor gets selected by overload resolution
        // but the "iterator" type is actually an integral type,
        // it has to delegate to the fill constructor by casting its argument types to force the latter to be an exact match.

        // Additionally, if InputIterator in the range constructor (3)
        // is not at least of a forward iterator category (i.e., it is just an input iterator)
        //, the new capacity cannot be determined beforehand and the construction incurs 
        //in additional logarithmic complexity in size (reallocations while growing).

        //	range constructor(3)
        template <class InputIterator>
        vector (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last,
                const allocator_type& alloc = allocator_type())
                    : _elements(NULL), _size(0), _capacity(0), _alloc(alloc)
        {
            assign(first, last);
        }

        // copy (4)
        vector (const vector& x) : _elements(NULL),  _size(0), _capacity(0), _alloc() { *this = x; }

        ~vector() { destroy_elements(); }

        vector& operator=( const vector& other ) // check if it works correctly!!! do we need to clear twice?
        {
            if (this == &other)
                return *this;
            if (!empty())
            {
                clear();
            }
            if (other._size > _capacity)
            {
                _alloc.deallocate(_elements, _capacity);
            }
			_alloc = other._alloc;
			assign(other.begin(), other.end());
			return *this;
        }

        allocator_type get_allocator() const
        {
            return _alloc;
        }

             // ELEMENT ACCESS:
        reference at(size_type pos)
        {
            if (pos >= _size)
            {
                throw std::out_of_range("at()");
            }
            return _elements[pos];
        }
        const_reference at(size_type pos) const
        {
            if (pos >= _size)
            {
                throw std::out_of_range("at()");
            }
            return _elements[pos];
        }
        reference back()
        {
            return _elements[_size - 1];
        }
        const_reference back() const
        {
            return _elements[_size - 1];
        }
//  turns out it's c++11:
//         pointer data() {
//             return _elements;
//         }
//         const_pointer data() const{
//             return _elements;
//         }
        reference front()
        {
            return _elements[0];
        }
        const_reference front() const
        {
            return _elements[0];
        }
        // If the container size is greater than n,
        // the function never throws exceptions (no-throw guarantee).
        //Otherwise, the behavior is undefined.
        reference operator[](size_type pos)
        {
            return _elements[pos];
        }
        const_reference operator[] (size_type pos) const
        {
            return _elements[pos];
        }

        // ITERATORS:
        iterator begin()
        {
            return _elements;
        }
        iterator end()
        {
            return _elements + _size;
        }
        const_iterator begin() const
        {
            return _elements;
        }
        const_iterator end() const
        {
            return _elements + _size;
        }
        reverse_iterator rbegin()
        {
            return reverse_iterator(end());
        }
        const_reverse_iterator rbegin() const
        {
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

    public:
        // assign() and operator= are pretty much equivalent. 
        //The reason for the second is that you might have types which need (implicit) conversion:
        // Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
       
        // range (1)
        template <class InputIterator> 
        void assign(typename ft::enable_if<ft::is_forward_iterator<InputIterator>::value, InputIterator>::type first, InputIterator last)
        {
            if (first == last)
                return;
            difference_type diff = std::distance(first, last);
            if (static_cast<size_type>(diff) > _capacity)
            {
                pointer temp = _alloc.allocate(diff);
                uninitialized_copy(temp, first, last);
                destroy_elements();
                _elements = temp;
                _capacity = diff;
            }
            else
            {
                clear();
                uninitialized_copy(_elements, first, last);
            }
            _size = diff;
        }

         // overload if the iterator is an input_iterator and not at least a forward iterator
        template <class InputIterator> 
        void assign(typename ft::enable_if<
            ft::is_input_iterator<InputIterator>::value && !ft::is_forward_iterator<InputIterator>::value, 
            InputIterator>::type first, InputIterator last)
        {
            clear();
			for (; first != last; ++first) 
            {
			    push_back(*first);
            }
        }

        // fill (2)
        void assign(size_type n, const value_type& val)
        {
            clear();
			resize(n, val);
        }

        // CAPACITY:
        size_type capacity() const
        {
            return _capacity;
        }
        bool empty() const
        {
            return (_size == 0);
        }
        size_type size() const
        {
            return _size;
        }
         //Returns the maximum theoretically possible value of n, for which the call allocate(n, 0) could succeed.
        size_type max_size() const
        {
            return _alloc.max_size();
        }

        // Correctly using reserve() can prevent unnecessary reallocations,
        //  but inappropriate uses of reserve() (for instance, calling it before every push_back() call)
        // may actually increase the number of reallocations (by causing the capacity to grow linearly rather than exponentially)
        // and result in increased computational complexity and decreased performance.
        void reserve(size_type new_cap)
        {
            if (new_cap <= _capacity)
            {
                return;
            }
            if (new_cap > max_size())
            {
                throw std::length_error("in reserve()");
            }
            pointer temp = _alloc.allocate(new_cap);
            uninitialized_copy(temp, _elements);
            destroy_elements(); // destroys them on current instance
            _elements = temp;
            _capacity = new_cap;
        }

        // MODIFIERS:
        void clear()
        {
            resize(0);
        }
        // Linear complexity: the number of calls to the destructor of T is the same as the number of elements erased,
        // the assignment operator of T is called the number of times equal to the number of elements in the vector after the erased elements
        iterator erase(iterator position)
        {
            size_type offset = position - begin();
            iterator it_end = end();
            _alloc.destroy(_elements + offset);
            if (position != it_end - 1)
            {
                for (iterator it = position; it + 1 !=it_end; ++it)
                {
                    *it = *(it + 1);
                }
            }
            _size--;
            return position;
        }

        iterator erase(iterator first, iterator last)
        {
            if (first == last)
            {
                return first;
            }
            difference_type offset = first - begin();
            difference_type num_to_erase = last - first;
            destroy_range(_elements + offset, _elements + offset + num_to_erase);
            iterator it_end = end();
            for (iterator iter = first; iter + num_to_erase != it_end; ++iter)
            {
                *iter = *(iter + num_to_erase);
            }
            _size -= num_to_erase;
            return first;
        }

        iterator insert(iterator position, const value_type& val)
        {
            pointer start = move_elements_forward(position, 1);
            uninitialized_fill(start, start + 1, val);
            _size++;
            return iterator(start);
        }


        // fill (2)	//  (return: Iterator pointing to the first element inserted, or pos if count==0) how is it possible if return type is void?
        void insert(iterator position, size_type n, const value_type& val)
        {
            pointer start = move_elements_forward(position, n);
            uninitialized_fill(start, start + n, val);
            _size += n;
        }

        // range (3)	
        template <class InputIterator>
        void insert (iterator position, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
        {
            // size_type distance = last - first;

            difference_type distance = std::distance(first,last);
            // std::cout << "distance: " << distance << std::endl;
            pointer start = move_elements_forward(position, distance);
            uninitialized_copy(start, first, last);
            _size += distance;
        }

        void pop_back()
        {
            // If the container is not empty, the function never throws exceptions (no-throw guarantee).
            // Otherwise, it causes undefined behavior. (so no empty() check)
            _size--;
            _alloc.destroy(_elements + _size);
        }

        void push_back( const T& value )
        {
            if (_capacity == _size)     // no more free space; relocate:
                reserve(_size? 2 * _size : 2);  // grow or start with 8 - recommendation from Stroustrup's book (because does it make sense to do otherwise?)
            _alloc.construct(_elements + _size, value); // add val at end
            _size++;
        }
        // Using resize() on a vector is very similar to using the C standard library function realloc() on a C array allocated on the free store.
        // Resizes the container so that it contains n elements.
        void resize(size_type n, value_type val = value_type())
        {
            if (n > _size)
            {
                reserve(n);
                while (n > _size)
                {
                    push_back(val);
                }
            }
            else
            {
                destroy_range(_elements + n, _elements + _size);
                _size = n;
            }
        }

    //Notice that a non-member function exists with the same name, 
    //swap, overloading that algorithm with an optimization that behaves like this member function.
        
        void swap (vector& x) // partial specialization for vector swap function
        {
            ft::swap(x._elements, _elements);
            ft::swap(x._size, _size);
            ft::swap(x._capacity, _capacity);
            ft::swap(x._alloc, _alloc);
        };
            void uninitialized_fill(pointer start, pointer end, const value_type& val)
        {
            pointer ptr, ptr1; // ptr1 for destructing if construction fails
            try
            {
                for (ptr = start; ptr != end; ++ptr)
                {
                    _alloc.construct(ptr, val); // constructs an element object on the location pointed by ptr.
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                for (ptr1 = start; ptr1 != ptr; ++ptr1)
                {
                    _alloc.destroy(ptr1);
                }
                    throw; //rethrow
            }
        }

        void uninitialized_copy(pointer dest, pointer src)
        {
            pointer dest_ptr = dest, src_ptr = src;
            for (; dest_ptr != dest + _size; ++src_ptr, ++dest_ptr)
            {
                try // if there are exception from the constructor
                {
                    _alloc.construct(dest_ptr, *src_ptr); // The calls to alloc.construct() in the vector constructors are simply syntactic sugar for the placement new.
                }
                catch (...) // (...)will be catching any exception
                {
                    for (; dest != dest_ptr; ++dest)
                    {
                        _alloc.destroy(dest); // if anything throws an exception, the container is guaranteed to end in a valid state (basic guarantee)
                    }
                    throw;
                }
            }
        }

        template <class InputIterator> 
        void uninitialized_copy(pointer dest, InputIterator src_first, InputIterator src_last)
        {
            pointer dest_start = dest; // needed for destruction in case the alloc is throwing the exception 
            for (InputIterator it = src_first; it != src_last; ++it, ++dest)
            {
                try
                {
                    _alloc.construct(dest, *it);
                }
                catch (...) // (...)will be catching any exception
                {
                    for (; dest_start != dest; ++dest_start)
                    {
                        _alloc.destroy(dest); // if anything throws an exception, the container is guaranteed to end in a valid state (basic guarantee)
                    }
                    throw;
                }
            }
        }

        // returns the pointer to the poaition that will be filled with the new value
        pointer move_elements_forward(iterator position, size_type n)
        {
            const size_type newsize = _size + n;
            difference_type distance = position - begin();
            if (newsize > _capacity) // no more free space; relocate:
            {
                reserve(newsize);
                position = begin() + distance;
            }
            iterator it = position;
            if (!empty())
            {
                it = end() - 1;
                for (; it != (position - 1); --it) // moving from the last element to the position(included)
                {
                    *(it + n) = *(it);
                }
            }
            pointer start = _elements + distance;
            return start;
        }

        // WHY TO USE DESTRUCT AND DEALLOCATE:
        // A program may end the lifetime of any object by reusing the storage which the object occupies
        // or by explicitly calling the destructor for an object of a class type with a non-trivial destructor.
        // For an object of a class type with a non-trivial destructor,
        //  the program is not required to call the destructor explicitly
        //  before the storage which the object occupies is reused or released;
        // however, if there is no explicit call to the destructor
        // or if a delete-expression (5.3.5) is not used to release the storage,
        //  the destructor shall not be implicitly called and any program that depends on the side effects
        //  produced by the destructor has undeﬁned behavior.

        void destroy_range(pointer destroy_start, pointer destroy_end)
        {
            for (; destroy_start != destroy_end; ++destroy_start)
            {
                _alloc.destroy(destroy_start);
            }
        }

        void destroy_elements()
        {
            pointer end = _elements + _size;
            for (pointer ptr = _elements; ptr != end; ++ptr)
            {
                _alloc.destroy(ptr); // Calls the destructor of the object
            }
            _alloc.deallocate(_elements, _size); // Deallocates the storage referenced by the pointer p, which must be a pointer obtained by an earlier call to allocate()
        }
    
    };

    // NON_MEMBER OVERLOADS:
    template< class T>
    void swap (vector<T>& x, vector<T>& y)
    {
        x.swap(y);
    }

    //relational operators (vector):
    template <class T, class Alloc>
    bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <class T, class Alloc>
    bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class T, class Alloc>
    bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template <class T, class Alloc>
    bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(rhs < lhs); // reusing operator<() but changing the sides
    }

    template <class T, class Alloc>
    bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return rhs < lhs;
    }

    template <class T, class Alloc>
    bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(lhs < rhs);
    }
}

#endif
