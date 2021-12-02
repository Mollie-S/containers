#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory> //needed for allocator
#include <iostream>
#include <cmath>
#include "enable_if.hpp"

namespace ft
{
    template <class T, class Alloc = ::std::allocator<T> > // generic template
    class vector
    {
        //  iterators are an abstraction of pointers
        class iterator // Iterator base class
        {
            // This base class only provides some member types,
            // which in fact are not required to be present in any iterator type
            // (iterator types have no specific member requirements),
            // but they might be useful,
            //since they define the members needed for the default iterator_traits class template
            //to generate the appropriate instantiation automatically
            //(and such instantiation is required to be valid for all iterator types).

        public:
            typedef T                                       value_type; // cannot use "using as it is c++11"
            typedef Alloc                                   allocator_type;
            typedef size_t                                  size_type;
            typedef value_type&                             reference;
            typedef value_type const &                      const_reference;
            typedef typename allocator_type::pointer        pointer;
            typedef typename allocator_type::const_pointer  const_pointer;
            typedef std::ptrdiff_t                          difference_type;
            typedef std::random_access_iterator_tag         iterator_category;

                // random_access_iterator -  Empty class to identify the category of an iterator as a random-access iterator:

                // DO we define value_type etc fron iterator_traits????::::

                //             value_type, the type denoted by std::iterator_traits<It>::value_type
                // difference_type, the type denoted by std::iterator_traits<It>::difference_type
                // reference, the type denoted by std::iterator_traits<It>::reference

            pointer _ptr;

        public:
            iterator() : _ptr(NULL) {}
            iterator(T* d) : _ptr(d) {}
            iterator(const iterator& it) : _ptr(it._ptr) {}
            ~iterator(){};

            iterator& operator=(const iterator& i)
            {
                _ptr = i._ptr;
                return (*this);
            }
            reference operator*()
            {
                return (*_ptr);
            }
            reference operator*() const
            {
                return (*_ptr);
            }
            pointer operator->()
            {
                return (_ptr);
            }
            pointer operator->() const
            {
                return (_ptr);
            }

            //  ARITHMETIC OPERATORS
            iterator& operator++()
            {
                _ptr++;
                return *this;
            }
            iterator operator++(int) // postfix operator as it accepts an argument
            {
                iterator temp = *this;
                ++(*this);
                return temp;
            }
            iterator& operator--()
            {
                _ptr--;
                return *this;
            }
            iterator operator--(int)
            {
                iterator temp = *this;
                --(*this);
                return temp;
            }
            iterator& operator+=(const int &val)
            {
                _ptr += val;
                return (*this);
            }
            iterator& operator-=(const int &val)
            {
                _ptr -= val;
                return (*this);
            }
            // RELATIONAL OPERATORS
            bool operator<(const iterator& rhs) const
            {
                return _ptr < rhs._ptr;
            }
            bool operator>(const iterator& rhs)
            {
                return _ptr > rhs._ptr;
            }
            bool operator<=(const iterator& rhs) const
            {
                return _ptr <= rhs._ptr;
            }
            bool operator>=(const iterator& rhs)
            {
                return _ptr >= rhs._ptr;
            }
        };


        // friend iterator operator+(vector<T, Allocator>::iterator lhs, const int &rhs)
        // {
        //     lhs += rhs;
        //     return (lhs);
        // }
        // friend iterator operator-(vector<T, Allocator>::iterator lhs, const int &rhs)
        // {
        //     lhs -= rhs;
        //     return (lhs);
        // }
        friend bool operator==(const iterator& lhs, const iterator& rhs)
        {
            return (lhs.ptr == rhs.ptr);
        }
        friend bool operator!=(const iterator& lhs, const iterator& rhs) { return !(lhs == rhs); }

        // typedef 	iterator;// convertible to const iterator?????  another subclass with const iterator???

        typedef typename iterator::value_type       value_type;
        typedef typename iterator::allocator_type   allocator_type;
        typedef typename iterator::reference        reference;
        typedef typename iterator::const_reference  const_reference;
        typedef typename iterator::pointer          pointer;
        typedef typename iterator::const_pointer    const_pointer;
        typedef typename iterator::difference_type  difference_type;
        typedef typename iterator::size_type        size_type;

    private:
        pointer         _elements;     // pointer to the first element of the container
        size_type       _size;       // num of elements in the container
        size_type       _capacity;   // capacity of the container
        allocator_type  _alloc; // the type of the allocator used

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

        void ft_destroy(vector &destroy_start, vector &destroy_end)
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
        // vector (const vector& x); 

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

        // If the container size is greater than n,
        // the function never throws exceptions (no-throw guarantee).
        //Otherwise, the behavior is undefined.

        reference operator[](size_type pos)
        {
            return _elements[pos];
        }

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
        void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
        {
			clear();
			for (; first != last; ++first)
			push_back(*first);
        }

        // fill (2)
        void assign (size_type n, const value_type& val)
        {
            clear();
			resize(n, val);
        }

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

        size_type capacity() const
        {
            return _capacity;
        }

        void clear()
        {
            resize(0);
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
                reserve(_size? 2 * _size : 8);  // grow or start with 8 - recommendation from Stroustrup's book
            _alloc.construct(_elements + _size, value); // add val at end
            _size++;
        }


        // Using resize() on a vector is very similar to using the C standard library function realloc() on a C array allocated on the free store.
        void resize(size_type n, value_type val = value_type())
        {
            reserve(n);
            if (_size < n)
            {
                uninitialized_fill(_elements + _size, _elements + n, val); // pointer to the elements will be updated
            }
            else
            {
                ft_destroy(_elements + n, _elements + _size);
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
            destroy_elements();
            _elements = temp;
            _capacity = new_cap;
        }

        void swap(vector &x) // ft_swap!!!! thanks Maarten!
        {
            pointer temp = _elements;
            size_t temp_size = _size;
            size_t temp_capacity = _capacity;
            allocator_type temp_alloc = _alloc;

            _elements = x._elements;
            _size = x._size;
            _capacity = x._capacity;
            _alloc = x._alloc;

            x._elements = temp._elements;
            x._size = temp._size;
            x._capacity - temp._capacity;
            x._alloc = temp._alloc;
        }
    };
};

#endif
