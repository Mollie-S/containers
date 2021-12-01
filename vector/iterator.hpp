#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace ft
{
	template<class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template<class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template<class Category, class T, class Distance = ptrdiff_t,
			class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};

	struct input_iterator_tag  {};
	struct output_iterator_tag {};
	struct forward_iterator_tag       : public input_iterator_tag         {};
	struct bidirectional_iterator_tag : public forward_iterator_tag       {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
}


	// vector with iterators:
	



				// iterators
		iterator begin(){ return iterator(_elements); } // No-throw guarantee: this member function never throws exceptions.The copy construction or assignment of the returned iterator is also guaranteed to never throw.
		const_iterator begin() const { return const_iterator(_elements); }

		iterator end() { return iterator(_elements + _size); }
		const_iterator end() const { return const_iterator(_elements + _size); }

		reverse_iterator rbegin() { return reverse_iterator (end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

		reverse_iterator rend() { return reverse_iterator (begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator (begin()); }


			vector& operator=( const vector& other )
	{
		reserve(other.size() == 0 ? 1 : other.size() * 2);
		for (size_t i = 0; i < other._size; i++)
			push_back(other.ptr[i]);

		return *this;
	}




	void assign( size_t count, const T& value )
	{
		clear();
		resize(count, value);
	}

	template< class InputIt>
	void assign( InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0)
	{
		clear();
		for (; first != last; first++)
			push_back(*first);
	}

	bool empty() const {return !!!_size;}
	size_type size() const {return _size;}
	size_type capacity() const {return _capacity;}
	size_type max_size() const {return (std::numeric_limits<std::ptrdiff_t>::max() / sizeof(T) * 2 + 1);}
	// void clear() {
	// 	_alloc.deallocate(ptr, _capacity);
	// 	_size = 0;
	// 	_capacity = 0;
	// 	ptr = 0;
	// }

	reference back() {return ptr[_size == 0 ? 0 : _size - 1];}
	reference front() {return ptr[0];}
	const_reference front() const {return ptr[0];}
	const_reference back() const {return ptr[_size == 0 ? 0 : _size - 1];}


	T	*data() {return ptr;}
	const T	*data() const {return ptr;}

	allocator_type get_allocator() const { return _alloc;}


	reference operator[](size_type idx)
	{
		return ptr[idx];
	}
	const_reference operator[](size_type idx ) const
	{
		return ptr[idx];
	}
	
	reference  at(size_type pos)
	{
		if (pos >= _size)
			throw std::out_of_range("out of range");
		return (ptr[pos]);
	}
	const_reference at(size_type pos) const
	{
		if (pos >= _size)
			throw std::out_of_range("out of range");
		return (ptr[pos]);
	}
	void resize( size_type count, T value = T() )
	{
		T *new_addr;
		if (count > _capacity)
			new_addr = _alloc.allocate(count);
		else
			new_addr = ptr;
		for (size_t i = 0; ptr != new_addr && i < count && i < _size; i++)
			new_addr[i] = ptr[i];
		for (size_t i = _size; i < count; i++)
			new_addr[i] = value;
		
		if (ptr != new_addr)
		{
			_alloc.deallocate(ptr, _capacity);
			_capacity = count;
			ptr = new_addr;
		}
		_size = count;
	}


	iterator begin()		{return iterator(ptr);}
	iterator end()			{return iterator(ptr + _size);}	
	iterator begin() const	{return iterator(ptr);}
	iterator end()	const	{return iterator(ptr + _size);}

	reverse_iterator rbegin()		{return reverse_iterator(ptr + _size - 1);}
	reverse_iterator rbegin() const	{return reverse_iterator(ptr + _size - 1);}
	reverse_iterator rend()			{return reverse_iterator(ptr - 1);}
	reverse_iterator rend() const	{return reverse_iterator(ptr - 1);}

	iterator insert( iterator pos, const T& value )
	{
		insert(pos, 1, value);
		return (pos);
	}

	void insert  ( iterator pos, size_t count, const T& value )
	{
		size_t i_pos = 0;
		if (ptr != 0)
			i_pos = &*pos - ptr;

		if (_size + count > _capacity)
			reserve(_size == 0 ? count : _size * 2);
		for (size_t i = _size + count; i >= i_pos + count; i--)
			ptr[i] = ptr[i - count];
		for (size_t i = 0; i < count; i++)
			ptr[i_pos + i] = value;
		_size += count;
	}

	template< class InputIt>
	void insert( iterator pos, InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value, InputIt>::type* = 0)
	{	
		size_t i_pos = 0;
		if (ptr != 0)
			i_pos = &*pos - ptr;
		size_t count = distance(first, last);

		// std::cout << "p--------------------------"<< i_pos << " " << count << " " << _size << std::endl;
		if (_size + count > _capacity)
			reserve(_size == 0 ? count : _size * 2);
		for (size_t i = _size + count; i > i_pos + count; i--)
			ptr[i] = ptr[i - count];
		size_t x = 0;
		for (InputIt it = first; x < count && it != last; x++, it++)
			_alloc.construct(&ptr[x + i_pos], *it);
		_size += count;
	}

	iterator erase(iterator pos )
	{
		size_t i = &*pos - ptr + 1;
		for (; i < _size; i++)
			ptr[i - 1] = ptr[i];
		_size--;
		return (pos);
	}

	iterator erase( iterator first, iterator last )
	{
		size_t i = &*first - ptr + 1;
		size_t endi = &*last - ptr + 1;

		for (; i < endi; i++)
			first = erase(first);
		return (first);
	}

};

template<class T>
bool operator==(const vector<T>& lhs, const vector<T>& rhs )
{
	if (lhs.size() != rhs.size())
		return (false);
	for (size_t i = 0; i < rhs.size(); i++)
		if (rhs[i] != lhs[i])
			return (false);
	return (true);
}

template<class T>
bool operator!=(const vector<T>& lhs, const vector<T>& rhs ) {return !(lhs == rhs);}

template< typename T>
bool operator<(const vector<T> &lhs, const vector<T> &rhs)
{
	size_t l1 = 0, r1 = 0;
	size_t l_size = lhs.size(), r_size = rhs.size();
	for (; l1 < l_size && r1 < r_size; l1++, r1++) {
		if (lhs[l1] < rhs[r1]) return true;
        if (rhs[l1] < lhs[r1]) return false;
	}
	return (l1 == l_size) && (r_size != r1);
}

template< typename T>
bool operator>(const vector<T> &lhs, const vector<T> &rhs) {return rhs < lhs;}
template< typename T>
bool operator>=(const vector<T> &lhs, const vector<T> &rhs) {return !(lhs < rhs);}
template< typename T>
bool operator<=(const vector<T> &lhs, const vector<T> &rhs) {return !(lhs > rhs);}

template< typename T >
void swap( ft::vector<T>& lhs, ft::vector<T>& rhs )
{
	lhs.swap(rhs);
}



#endif
