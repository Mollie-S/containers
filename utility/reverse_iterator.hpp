#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{
	template <class Iterator> 
	class reverse_iterator
	{
	public:
		typedef Iterator                                           				iterator_type;
		typedef typename ft::iterator_traits<iterator_type>::iterator_category 	iterator_category;
		typedef typename ft::iterator_traits<iterator_type>::value_type        	value_type;
    	typedef typename ft::iterator_traits<iterator_type>::difference_type   	difference_type;
    	typedef typename ft::iterator_traits<iterator_type>::pointer           	pointer;
    	typedef typename ft::iterator_traits<iterator_type>::reference         	reference;

	private:
		iterator_type _current;

	public:
		// default (1)	
		reverse_iterator() : _current() {}
		// initialization (2)	
		explicit reverse_iterator (iterator_type it) : _current(it) {}
		// copy (3)	
		template<typename Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it) : _current(rev_it.base()) {}


		//Returns a copy of the base iterator.
		// The base iterator is an iterator of the same type 
		//as the one used to construct the reverse_iterator,
		// but pointing to the element next to the one 
		//the reverse_iterator is currently pointing to 
		//(a reverse_iterator has always an offset of -1 with respect to its base iterator).
		iterator_type base() const
		{
			return _current;
		}
		//Returns a reference to the element pointed to by the iterator.
		// Internally, the function decreases a copy of its base iterator and returns the result of dereferencing it.
		// The iterator shall point to some object in order to be dereferenceable.
		reference operator*() const
		{
			iterator_type temp = _current; 
			return *(--temp);
		}
		//Internally, the function applies the binary operator- on the base iterator 
		//and returns a reverse iterator constructed with the resulting iterator value.
		reverse_iterator operator+ (difference_type n) const
		{
			return reverse_iterator(_current - n);
		}
		// (1) pre-increment version:
		reverse_iterator& operator++()
		{
			--_current;  //not ++
			return *this;
		}
		// (2)	The post-increment version:
		reverse_iterator  operator++(int)
		{
			reverse_iterator temp(*this);
			--_current;
			return temp;
		}
		//Modifies the object.
		reverse_iterator& operator+= (difference_type n)
		{
			_current -= n;
			return *this;
		}
		reverse_iterator operator- (difference_type n) const
		{
			return reverse_iterator(_current + n);
		}
		reverse_iterator& operator-= (difference_type n)
		{
			_current += n;
			return *this;
		}
		reverse_iterator& operator--()
		{
			++_current; //not --
			return *this;
		}
		reverse_iterator  operator--(int)
		{
			reverse_iterator temp(*this);
			++_current;
			return temp;
		}
		pointer operator->() const
		{
			return &(operator*());
		}
		// If the element with position n does not exist, it causes undefined behavior.
		// Internally, the function accesses the proper element of its base iterator, returning the same as: base()[-n-1].
		reference operator[] (difference_type n) const
		{
			return (base()[-n - 1]);
		}
	};

	// NON_MEMBER OVERLOADS:
		
template <class Iterator1, typename Iterator2>
bool operator== (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
	return lhs.base() == rhs.base();
}

template <class Iterator1, typename Iterator2>
bool operator!= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
	return lhs.base() != rhs.base();
}

template <class Iterator1, typename Iterator2>
bool operator<  (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
	return lhs.base() > rhs.base(); // not <!!!
}

template <class Iterator1, typename Iterator2>
bool operator<= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
	return lhs.base() >= rhs.base(); // not <=!!!
}

template <class Iterator1, typename Iterator2>
bool operator>  (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
	return lhs.base() < rhs.base();
}

template <class Iterator1, typename Iterator2>
bool operator>= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
	return lhs.base() <= rhs.base();
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator- (
    const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs)
	{
		return rhs.base() - lhs.base();
	}

template <class Iterator>
reverse_iterator<Iterator> operator+ (
             typename reverse_iterator<Iterator>::difference_type n,
             const reverse_iterator<Iterator>& rev_it)
			 {
				return reverse_iterator<Iterator>(rev_it.base() - n);
			 }
}
#endif
