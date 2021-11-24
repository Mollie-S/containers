#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory> //needed for allocator
#include <iostream>
#include <cmath>

namespace ft
{
    template <class T, class Alloc = std::allocator<T>> // generic template
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
            for (size_type i = 0; i != _size; ++i)
            { // using index not to create 2 pointers
                try
                {
                    _alloc.construct(temp[i], _elements[i]); // need to try and catch possible exception from the constructor
                    _alloc.destroy(_elements[i]);
                }
                catch (...)
                { // (...)will be catching any exception
                    for (size_type j = 0; j != i; ++j)
                    {
                        _alloc.destroy(temp[j]); // if anything throws an exception, the container is guaranteed to end in a valid state (basic guarantee)
                    }
                    throw;
                }
            }
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
 
 // If T is a type for which it can be expensive to copy elements, such as string and vector, the usual swap()
// becomes an expensive operation. Note something curious: we didn’t want any copies at all; we just
// wanted to move the values of a, b, and tmp around. We can tell that to the compiler:
        void swap(T &a, T &b) // "perfect swap" (almost)
        {
            T tmp{static_cast<T &&>(a)}; // the initialization may write to a
            a = static_cast<T &&>(b);    // the assignment may write to b
            b = static_cast<T &&>(tmp);  // the assignment may write to tmp
        }
    };
    // The result value of static_cast<T&&>(x) is an rvalue of type T&& for x.
    // An operation that is optimized for rvalues can now use its optimization for x. 
    //In particular, if a type T has a move constructor (§3.3.2, §17.5.2) or a move assignment, it will be used.
//     The use of static_cast in swap() is a bit verbose and slightly prone to mistyping, so the standard
// library provides a move() function: move(x) means static_cast<X&&>(x) where X is the type of x.
};

#endif
