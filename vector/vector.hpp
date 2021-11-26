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

        void uninitialized_copy(const vector& dest, const vector& src)
        {
            for (size_type i = 0; i != src._size; ++i)
            { // using index not to create 2 pointers
                try
                {
                    _alloc.construct(dest[i], src[i]); // need to try and catch possible exception from the constructor
                }
                catch (...)
                { // (...)will be catching any exception
                    for (size_type j = 0; j != i; ++j)
                    {
                        _alloc.destroy(dest[j]); // if anything throws an exception, the container is guaranteed to end in a valid state (basic guarantee)
                    }
                    throw;
                }
            }
        }

        void destroy_elements(vector& src)
        {
            for (size_type i = 0; i != src._size; ++i)
            {
                _alloc.destroy(src[i]);
            }
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

            pointer ptr, ptr1;
            try
            {
                pointer end = _elements + n;
                for (ptr = _elements; ptr != end; ++ptr)
                {
                    _alloc.construct(ptr, val); // constructs an element object on the location pointed by p.
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                for (ptr1 = _elements; ptr1 != ptr; ++ptr1)
                {
                    _alloc.destroy(ptr1); // destructs an object stored in the allocated storage
                    throw;                //rethrow
                }
                _alloc.deallocate(_elements, n); // free memory
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

        ~vector()
        {
            pointer ptr;
            for (ptr = _elements; ptr != _elements + _size; ++ptr)
            {
                _alloc.destroy(ptr); // destructs an object stored in the allocated storage
            }
            _alloc.deallocate(_elements, _size); // free memory
        }

        vector& operator= (const vector& x)
        {
            if 
            _elements = _alloc.allocate(x._size);
            uninitialized_copy(this, x);

            destroy_elements(_elements);
            _alloc.deallocate(_elements, _size);
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

        void resize(size_type n, value_type val = value_type())
        {
            // add some code here
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
            _alloc.deallocate(_elements, _size);
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
        }

        //Unfortunately if T is a type for which it can be expensive to copy elements, such as string and vector, this swap()
        // becomes an expensive operation in versions under C++11
        
        void swap (vector& x)
        {
            T *temp = _elements;
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
