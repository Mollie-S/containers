#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
		// This base class only provides some member types,
		// which in fact are not required to be present in any iterator type
		// (iterator types have no specific member requirements),
		// but they might be useful,
		//since they define the members needed for the default iterator_traits class template
		//to generate the appropriate instantiation automatically
		//(and such instantiation is required to be valid for all iterator types).
	template <class Value>
	class vector_iter
	{
	public:
		typedef vector_iter<Value>                                              iterator_type;
		typedef typename ft::iterator_traits<iterator_type>::iterator_category 	iterator_category;
		typedef typename ft::iterator_traits<iterator_type>::value_type        	value_type;
    	typedef typename ft::iterator_traits<iterator_type>::difference_type   	difference_type;
    	typedef typename ft::iterator_traits<iterator_type>::pointer           	pointer;
    	typedef typename ft::iterator_traits<iterator_type>::reference         	reference;

	private:
		typedef vector_iter<const Value> const_iterator_type;

		pointer _ptr;
	public:
		vector_iter() : _ptr(NULL) {}
		vector_iter(pointer ptr) : _ptr(ptr) {}
		vector_iter(const iterator_type& other) : _ptr(other._ptr) {}
		~vector_iter(){};

		difference_type	distance(vector_iter first, vector_iter last)
		{
			difference_type count = 0;
			while (first + count != last)
				count++;
			return count;
		}

		vector_iter& operator=(const vector_iter& other)
		{
			if (*this != other)
			{
				_ptr = other._ptr;
			}
			return (*this);
		}

		reference operator*() const
		{
			return (*_ptr);
		}

		pointer operator->() const
		{
			return (_ptr);
		}

		// type conversion operator
		operator const_iterator_type() const
		{
			return const_iterator_type(_ptr);
		}

		//  ARITHMETIC OPERATORS
		vector_iter& operator++()
		{
			_ptr++;
			return *this;
		}

		vector_iter operator++(int) // postfix operator as it accepts an argument
		{
			vector_iter temp = *this;
			++(*this);
			return temp;
		}

		vector_iter& operator--()
		{
			_ptr--;
			return *this;
		}

		vector_iter operator--(int)
		{
			vector_iter temp = *this;
			--(*this);
			return temp;
		}

		vector_iter& operator+=(const int &val)
		{
			_ptr += val;
			return (*this);
		}

		vector_iter& operator-=(const int &val)
		{
			_ptr -= val;
			return (*this);
		}
		reference operator[](difference_type pos) const
        {
            return _ptr[pos];
        }

		// RELATIONAL OPERATORS
		bool operator<(const iterator_type& rhs) const
		{
			return _ptr < rhs._ptr;
		}

		bool operator>(const iterator_type& rhs)
		{
			return _ptr > rhs._ptr;
		}

		bool operator<=(const iterator_type& rhs) const
		{
			return _ptr <= rhs._ptr;
		}

		bool operator>=(const iterator_type& rhs)
		{
			return _ptr >= rhs._ptr;
		}

		friend vector_iter operator+(const iterator_type& lhs, const int rhs)
		{
			return (lhs._ptr + rhs);
		}

		friend vector_iter operator-(const iterator_type& lhs, const int rhs)
		{
			return (lhs._ptr - rhs);
		}

		friend difference_type operator-(const iterator_type& lhs, const iterator_type& rhs)
		{
			return (lhs._ptr - rhs._ptr);
		}

		friend bool operator==(const iterator_type& lhs, const iterator_type& rhs)
		{
			return (lhs._ptr == rhs._ptr);
		}

		friend bool operator!=(const iterator_type& lhs, const iterator_type& rhs) 
		{
			return !(lhs._ptr == rhs._ptr);
		}
	};

}
#endif
