#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory> //needed for allocator
#include <iostream>
#include <cmath>

namespace ft
{
    template <class T, class Alloc = ::std::allocator<T> > // generic template
    class vector
    {
        typedef T value_type; // cannot use "using as it is c++11"
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;

        // itetators need to be added here:
        // typedef 	iterator;// convertible to const iterator

        typedef ptrdiff_t difference_type;
        typedef size_t size_type;

    private:
        pointer _elements;     // pointer to the first element of the container
        size_type _size;       // num of elements in the container
        size_type _capacity;   // capacity of the container
        allocator_type _alloc; // the type of the allocator used


        void uninitialized_fill(pointer start, pointer end, value_type val)
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
                    throw;                //rethrow
                }
            }
        }

        void uninitialized_copy(const vector& dest, const vector& src)
        {
            for (size_type i = 0; i != src._size; ++i) // using index not to create 2 pointers s
            { 
                try // if there are exception from the constructor
                {
                    _alloc.construct(dest[i], src[i]);  // The calls to alloc.construct() in the vector constructors are simply syntactic sugar for the placement new. 
                }
                catch (...) // (...)will be catching any exception
                { 
                    for (size_type j = 0; j != i; ++j)
                    {
                        _alloc.destroy(dest[j]); // if anything throws an exception, the container is guaranteed to end in a valid state (basic guarantee)
                    }
                    throw;
                }
            }
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

        void destroy(vector& destroy_start, vector& destroy_end)
        {
             for (; destroy_start != destroy_end; ++destroy_start)
            {
                _alloc.destroy(destroy_start);
            }
        }

        void destroy_elements(vector& src)
        {
            for (size_type i = 0; i != src._size; ++i)
            {
                _alloc.destroy(src[i]); // Calls the destructor of the object
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
            _elements = _alloc.allocate(n); // get memory for elements
            try
            {
                uninitialized_fill(_elements, _elements + n, val);
            }
            catch(...)
            {
                _alloc.deallocate(_elements, n);
                throw;
            }
            
         
            std::cout << "Fill constructor called\n";
        }

        // the standard says that if the range constructor gets selected by overload resolution
        // but the "iterator" type is actually an integral type,
        // it has to delegate to the fill constructor by casting its argument types to force the latter to be an exact match.

        //	range constructor(3)
        // template <class InputIterator>
        // 		vector (InputIterator first, InputIterator last,
        // 				const allocator_type& alloc = allocator_type());

        // vector (const vector& x); // copy (4)

        ~vector() {destroy_elements(_elements);}

        vector& operator= (const vector& x) // check if it works correctly!!!
        {
            if (_size < x._size)
            {
                _elements = _alloc.allocate(x._size);
            }
            uninitialized_copy(this, x);
            destroy_elements(_elements);
            return this*;
        }

    public:
        // TO IMPLEMENT:
        // range (1)
        // template <class InputIterator>
        // void assign (InputIterator first, InputIterator last);
        // fill (2)
        // void assign (size_type n, const value_type& val)
        // {

        // }
        size_type size() const
        {
            return _size;
        }

        size_type max_size() const
        {
            return _alloc.max_size(); //Returns the maximum theoretically possible value of n, for which the call allocate(n, 0) could succeed.
        }

        // Using resize() on a vectoris very similar to using the C standard library function realloc() on a C array allocated on the free store.  
        void resize(size_type n, value_type val = value_type())  
        {
            reserve(n);
            if (_size < n)
            {
                uninitialized_fill(_elements + _size, _elements + n, val); // pointer to the elements will be updated
            }
            else
            {
                destroy(_elements + n, _elements + _size);
            }
            _size = n;
            _capacity = n;
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
            destroy_elements(_elements);
            _elements = temp;
            _capacity = new_cap;
        }

        size_type capacity() const
        {
            return _capacity;
        }

        bool empty() const
        {
            return (_size == 0);
        }

        void clear()
        {
            resize(0);
        }

        //Unfortunately if T is a type for which it can be expensive to copy elements, such as string and vector, 
        // this swap() becomes an expensive operation in versions under C++11
        
        void swap (vector& x)
        {
            pointer temp = _elements;
            size_t temp_size = _size;
            size_t temp_capacity = _capacity;
            _elements = x._elements;
            _size = x._size;
            _capacity = x._capacity;
            x._elements = temp._elements;
            x._size = temp._size;
            x._capacity - temp._capacity;
        }
    };
}

#endif
