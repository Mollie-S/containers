#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory> //needed for allocator
#include <iostream>

namespace ft
{
    template < class T, class Alloc = std::allocator<T> >   // generic template
    class vector
    {
        typedef T								            value_type;
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
        pointer         _last; // pointer to the first element of the container
        size_type       _size; // num of elements in the container
        size_type       _capacity; // capacity of the container
        allocator_type  _alloc; // the type of the allocator used


    public:
        //default constructor(1):
        explicit vector<T, Alloc>(const allocator_type& alloc = allocator_type())
        : _elements(NULL)
        , _last(NULL)
        , _capacity(0)
        , _size(0)
        , _alloc(alloc)
        {
            std::cout << "Default onstructor called\n";
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
                    _alloc.construct(ptr, val);
                }
                _last = ptr;
            }
             catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                  for(ptr1 = _elements; ptr1 != ptr; ++ptr1)
                {
                    _alloc.destroy(ptr1); // destroy constructed elements
                }
                _alloc.deallocate(_elements, n); // free memory
                throw; //rethrow
            }
        }
	
		// template <class InputIterator>
		// 		vector (InputIterator first, InputIterator last,
		// 				const allocator_type& alloc = allocator_type()); //	range (3)	

		// vector (const vector& x); // copy (4)

        ~vector(){}
        
    public:
        size_type size() const
        {
            return _size;
        }

        size_type capacity() const
        {
            return _capacity;
        }

        bool empty() const
        {
            return (_size == 0);
        }
    };
};

#endif