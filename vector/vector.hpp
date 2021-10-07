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
       
		typedef difference_type iterator_traits<iterator>::difference_type
		typedef size_type size_t

    // private:
        size_type _size;
        size_type _capacity;

    public:
		explicit vector<T, Alloc> (const allocator_type& alloc = allocator_type())
        : _size(0)
        , _capacity(0)//default
        {
            std::cout << "Constructor called\n";
        } 
	
		// explicit vector (size_type n, const value_type& val = value_type(),
		// 				const allocator_type& alloc = allocator_type()); //fill (2)
	
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
    };
};

#endif