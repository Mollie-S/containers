#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory> //needed for allocator
#include <iostream>
#include <cmath>
#include "enable_if.hpp"
#include "utils.hpp"
#include "vector_iterator.hpp"
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
        typedef vector_iter<pointer>                    iterator;
        typedef vector_iter<const_pointer>              const_iterator;
        //TODO 
        //reverse iterator must be implemented and std::reverse_iterator will be replaced
        typedef ::std::reverse_iterator<iterator>         reverse_iterator;
        typedef ::std::reverse_iterator<const_iterator>   const_reverse_iterator;

    private:
        pointer         _elements;     // pointer to the first element of the container
        size_type       _size;       // num of elements in the container
        size_type       _capacity;   // capacity of the container
        allocator_type  _alloc; // the type of the allocator used

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
                    throw; //rethrow
                }
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

      

        iterator ft_insert(iterator position, size_type n, const value_type& val)
        {
            iterator it_end = end();
            // do I replace it with unitia;ized copy???
            for (iterator current = it_end, prev = (current - n); current != (position - 1); --current, --prev)
            {
                *prev = *current;
            }
            size_type fill_start = position - begin();
            size_type fill_end = fill_start + n;
            uninitialized_fill(_elements + fill_start, _elements + fill_end, val);
            _size += n;
            return position;
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

        void ft_destroy(pointer destroy_start, pointer destroy_end)
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

    public:
        //default constructor(1):
        explicit vector<T, Alloc>(const allocator_type &alloc = allocator_type())
            : _elements(NULL), _capacity(0), _size(0), _alloc(alloc)
        {
            std::cout << "Default constructor called\n";
        }
        //fill constructor(2)
        explicit vector<T, Alloc>(size_type n, const value_type &val = value_type(),
                                  const allocator_type &alloc = allocator_type())
            : _capacity(n), _size(n), _alloc(alloc)
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

            std::cout << "Fill constructor called\n";
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
        vector (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0,
                const allocator_type& alloc = allocator_type())
                    : _elements(NULL), _capacity(0), _size(0), _alloc(alloc)
        {
            for (; first != last; ++first)
                push_back(*first);
        }

        // copy (4)
        vector (const vector& x) : _elements(NULL), _capacity(0), _size(0), _alloc() { *this = x; }

        ~vector() { destroy_elements(); }

        vector& operator=( const vector& other ) // check if it works correctly!!! do we need to clear twice?
        {
            if (this == &other)
                return *this;
			clear();
			_alloc.deallocate(_elements, _capacity);
			_alloc = other._alloc;
			assign(other.begin(), other.end());
			return *this;
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

        pointer data() {
            return _elements;
        }
        const_pointer data() const{
            return _elements;
        }
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


        // ITERATORS:
        iterator begin()
        {
            return _elements;
        }

        iterator end()
        {
            return _elements + _size;
        }
// TODO:
        // const_iterator begin() const
        // {

        // }

        // const_iterator end() const
        // {

        // }
        // reverse_iterator rbegin()
        // {

        // }
        // const_reverse_iterator rbegin() const
        // {

        // }


    public:
        // assign() and operator= are pretty much equivalent. 
        //The reason for the second is that you might have types which need (implicit) conversion:
        // range (1)
        
        // Additionally, in the range version (1), 
        //if InputIterator is not at least of a forward iterator category
        // (i.e., it is just an input iterator) the new capacity cannot be determined beforehand 
        //and the operation incurs in additional logarithmic complexity in the new size (reallocations while growing).




        // TO DO enableif with input iterarator?????
        template <class InputIterator> 
        void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
        {
			clear();
			for (; first != last; ++first)
			push_back(*first);
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
            destroy_elements();
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
        iterator erase (iterator position)
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
        iterator erase (iterator first, iterator last)
        {
            iterator it_start = begin();
            difference_type followingLastRemovedElement = first - it_start;

            size_type first_offset = first - it_start;
            size_type last_offset = last - it_start;
            ft_destroy(_elements + first_offset, _elements + last_offset);

            iterator it_end = end();
            if (last != it_end)
            {
                for (iterator it = first; it + 1 !=it_end; ++it, ++last)
                {
                    *it = *(last);
                }
            }
            _size -= (last_offset - first_offset);
            return begin() + followingLastRemovedElement;
        }

        // TODO: REWRITE WITH ASSIGN 1 ELEMENT AND REVERSE OPERATOR:
        iterator insert(iterator position, const value_type& val)
        {
            ft_insert(position,1,val);
        }
        // TODO: use assign with reverse iterator!
        // fill (2)	//  (return: Iterator pointing to the first element inserted, or pos if count==0) how is it possible if return type is void?
        void insert(iterator position, size_type n, const value_type& val)
        {
            const size_type newsize = _size + n;
            if (newsize > _capacity) // no more free space; relocate:
            {
                reserve(newsize);
            }
            ft_insert(position,n,val);
        }

        // TODO:
        // range (3)	
        // template <class InputIterator>
        // void insert (iterator position, InputIterator first, InputIterator last)
        // {
        //     size_type distance = last - first;
        //     const size_type newsize = _size + distance;
        //     if (newsize > _capacity)
        //     {
        //         reserve(newsize);
        //     }
                
        // }
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
                ft_destroy(_elements + n, _elements + _size);
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
    
    };

    template< class T>
    void swap (vector<T>& x, vector<T>& y)
    {
        x.swap(y);
    };
};

#endif
