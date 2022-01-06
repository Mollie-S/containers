#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include "../utility/iterator_traits.hpp"

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

		// means that map_iter specialized for any types can get access to the map iter of these types
		template <typename T>
		friend class vector_iter;

	private:
		pointer _ptr;
	public:
		vector_iter() : _ptr(NULL) {}
		vector_iter(pointer ptr) : _ptr(ptr) {}
		// template function inside of a template accepting vector_iter for different value types
		// this allows to cast from non-const to const
		template<typename T>
		vector_iter(const vector_iter<T>& other) : _ptr(other._ptr) {}
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


		// EQUALITY/INEQUALITY OPERATORS:
		template<typename T>
		bool operator==(const vector_iter<T>& other) const
		{
			return (_ptr == other._ptr);
		}

		template<typename T>
		bool operator!=(const vector_iter<T>& other) const
		{
			return (_ptr != other._ptr);
		}

		// TODO: add templated parameters
		// RELATIONAL OPERATORS
		bool operator<(const vector_iter& rhs) const
		{
			return _ptr < rhs._ptr;
		}

		bool operator>(const vector_iter& rhs)
		{
			return _ptr > rhs._ptr;
		}

		bool operator<=(const vector_iter& rhs) const
		{
			return _ptr <= rhs._ptr;
		}

		bool operator>=(const vector_iter& rhs)
		{
			return _ptr >= rhs._ptr;
		}

		friend vector_iter operator+(const vector_iter& lhs, const int rhs)
		{
			return (lhs._ptr + rhs);
		}

		friend vector_iter operator-(const vector_iter& lhs, const int rhs)
		{
			return (lhs._ptr - rhs);
		}

		friend difference_type operator-(const vector_iter& lhs, const vector_iter& rhs)
		{
			return (lhs._ptr - rhs._ptr);
		}

		friend bool operator==(const vector_iter& lhs, const vector_iter& rhs)
		{
			return (lhs._ptr == rhs._ptr);
		}

		friend bool operator!=(const vector_iter& lhs, const vector_iter& rhs) 
		{
			return !(lhs._ptr == rhs._ptr);
		}
	};

}
#endif
