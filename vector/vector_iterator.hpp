#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

namespace ft
{
		// This base class only provides some member types,
		// which in fact are not required to be present in any iterator type
		// (iterator types have no specific member requirements),
		// but they might be useful,
		//since they define the members needed for the default iterator_traits class template
		//to generate the appropriate instantiation automatically
		//(and such instantiation is required to be valid for all iterator types).
	template <class Iterator>
	class vector_iter // Iterator base class
	{
	
	//TODO
	// replace std with ft when iterator_traits implemented:
	public:
		typedef Iterator                                                      		iterator_type;
		typedef typename ::std::iterator_traits<iterator_type>::value_type        	value_type;
    	typedef typename ::std::iterator_traits<iterator_type>::difference_type   	difference_type;
    	typedef typename ::std::iterator_traits<iterator_type>::pointer           	pointer;
    	typedef typename ::std::iterator_traits<iterator_type>::reference         	reference;

			// random_access_iterator -  Empty class to identify the category of an iterator as a random-access iterator:

			//             value_type, the type denoted by std::iterator_traits<It>::value_type
			// difference_type, the type denoted by std::iterator_traits<It>::difference_type
			// reference, the type denoted by std::iterator_traits<It>::reference
	private:
		iterator_type _ptr;

	public:
		vector_iter() : _ptr(NULL) {}
		vector_iter(pointer ptr) : _ptr(ptr) {}
		vector_iter(const vector_iter& other) : _ptr(other._ptr) {}
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
		friend bool operator!=(const vector_iter& lhs, const vector_iter& rhs) { return !(lhs._ptr == rhs._ptr); }
	};

}
#endif
