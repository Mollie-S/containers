#ifdef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

namespace ft
{
    typedef std::allocator<T> allocator<T> 

    template < class T, class Alloc = allocator<T> >   // generic template
    class vector
    {
        typedef T								value_type;
        typedef Alloc							allocator_type;
        typedef allocator_type::reference		reference;
        typedef allocator_type::const_reference	const_reference;
        typedef allocator_type::pointer			pointer;
		typedef allocator_type::const_pointer	const_pointer;
		// add more!!!!!
    public:
		explicit vector (const allocator_type& alloc = allocator_type()); //default
	
		explicit vector (size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type()); //fill (2)
	
		template <class InputIterator>
				vector (InputIterator first, InputIterator last,
						const allocator_type& alloc = allocator_type()); //	range (3)	

		vector (const vector& x); // copy (4)

        ~vector(){}
    };
};



#endif