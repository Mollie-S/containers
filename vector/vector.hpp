#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory> //needed for allocator
#include <iostream>
#include <cmath>

namespace ft
{
    template < class T, class Alloc = std::allocator<T> >   // generic template
    class vector
    {
        typedef T								            value_type; // cannot use "using as it is c++11"
        typedef Alloc							            allocator_type;
        typedef typename allocator_type::reference		    reference;
        typedef typename allocator_type::const_reference	const_reference;
        typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer	    const_pointer;

        // itetators need to be added here:
		// typedef 	iterator;// convertible to const iterator
       
		typedef ptrdiff_t                                   difference_type;
		typedef size_t                                      size_type;

    private:
        pointer         _elements; // pointer to the first element of the container
        size_type       _size; // num of elements in the container
        size_type       _capacity; // capacity of the container
        allocator_type  _alloc; // the type of the allocator used


    public:
        //default constructor(1):
        explicit vector<T, Alloc>(const allocator_type& alloc = allocator_type())
        : _elements(NULL)
        , _capacity(0)
        , _size(0)
        , _alloc(alloc)
        {
            std::cout << "Default constructor called\n";
        } 
         //fill constructor(2)
		explicit vector<T, Alloc>(size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type())
        : _capacity(n)
        , _size(n)
        , _alloc(alloc)
        {
                _elements = _alloc.allocate(n); // get memory for elements

            pointer ptr, ptr1;
            try
            {
                pointer end = _elements + n;
                for(ptr = _elements; ptr!= end; ++ptr)
                {
                    _alloc.construct(ptr, val); // constructs an element object on the location pointed by p.
                }
            }
             catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                  for(ptr1 = _elements; ptr1 != ptr; ++ptr1)
                {
                    _alloc.destroy(ptr1); // destructs an object stored in the allocated storage
                    throw; //rethrow
                }
                _alloc.deallocate(_elements, n); // free memory
            }
        }
         //	range constructor(3)	
		// template <class InputIterator>
		// 		vector (InputIterator first, InputIterator last,
		// 				const allocator_type& alloc = allocator_type());

		// vector (const vector& x); // copy (4)

        ~vector()
        {
            pointer ptr;
            for(ptr = _elements; ptr != _elements + _size; ++ptr)
            {
                _alloc.destroy(ptr); // destructs an object stored in the allocated storage
            }
            _alloc.deallocate(_elements, _size); // free memory
        }
        
    public:
        size_type size() const
        {
            return _size;
        }

        size_type max_size() const
        {
            return _alloc.max_size(); //Returns the maximum theoretically possible value of n, for which the call allocate(n, 0) could succeed.
        }

        void resize (size_type n, value_type val = value_type())
        {
            // add some code here
        }



// Correctly using reserve() can prevent unnecessary reallocations,
//  but inappropriate uses of reserve() (for instance, calling it before every push_back() call)
// may actually increase the number of reallocations (by causing the capacity to grow linearly rather than exponentially) 
// and result in increased computational complexity and decreased performance.
        void reserve(size_type new_cap)
        {
            // if (new_cap > max_size())
            // {
            //     throw std::length_error; 
            // }
            if (new_cap <= _capacity)
            {
                return;
            }
            try // do we need this block here?
            {
                pointer temp = _alloc.allocate(new_cap); // get memory for elements
                memmove(temp, _elements, _size);
                pointer ptr;
                for(ptr = _elements; ptr != _elements + _size; ++ptr)
                {
                    _alloc.destroy(ptr);
                }
                _alloc.deallocate(_elements, _size);
                _elements = temp;
                _capacity = new_cap;
            }
            catch (const std::length_error& e) // if n is greater than max size
            {
                std::cout << e.what() << "\n";
                throw; //rethrow
            }
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
    };
};

#endif
