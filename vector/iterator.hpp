#ifndef ITERATOR_HPP
#define ITERATOR_HPP


	// vector with iterators:
	template< class InputIt>
		vector( InputIt first, InputIt last, const Allocator& alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0): 
			_data(0), _size(0), _capacity(0), _alloc(alloc)
		{
			for (; first != last; first++)
				push_back(*first);
		}



		class iterator
	{
	public:
		typedef T 					value_type;
		typedef std::ptrdiff_t		difference_type;
		typedef size_t 				size_type;
		typedef value_type const&	const_reference;
		typedef value_type& 		reference;
		typedef	Allocator			allocator_type;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;

		typedef	T					iterator_category;
	protected:
		T		*_data;
	public:
		iterator(T *d): _data(d) {}
		iterator &operator=(const iterator &i)
		{
			_data = i._data;
			return (*this);
		}
		~iterator() {};
		iterator& operator++()
		{
			_data++;
			return *this;
		}
		iterator& operator--()
		{
			_data--;
			return *this;
		}
		iterator operator++(int)
		{
			iterator old = *this;
			operator++();
			return (*this);
		}
		iterator operator--(int)
		{
			iterator old = *this;
			operator--();
			return (*this);
		}
		iterator &operator+=(const int &val)
		{
			_data += val;
			return (*this);
		}
		friend iterator operator+(vector<T, Allocator>::iterator lhs, const int &rhs)
		{
			lhs += rhs;
			return (lhs);
		}
		iterator &operator-=(const int &val)
		{
			_data -= val;
			return (*this);
		}
		friend iterator operator-(vector<T, Allocator>::iterator lhs, const int &rhs)
		{
			lhs -= rhs;
			return (lhs);
		}
	
		friend bool operator==(const iterator& lhs, const iterator& rhs)
		{
			return (lhs._data == rhs._data);
		}
		friend bool operator!=(const iterator& lhs, const iterator& rhs) {return !(lhs == rhs);}
		const T	&operator*() const
		{
			return (*_data);
		}
		T	&operator*()
		{
			return (*_data);
		}
		T	*operator->()
		{
			return (_data);
		}
	};


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
			push_back(other._data[i]);

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
	void clear() {
		_alloc.deallocate(_data, _capacity);
		_size = 0;
		_capacity = 0;
		_data = 0;
	}

	reference back() {return _data[_size == 0 ? 0 : _size - 1];}
	reference front() {return _data[0];}
	const_reference front() const {return _data[0];}
	const_reference back() const {return _data[_size == 0 ? 0 : _size - 1];}


	T	*data() {return _data;}
	const T	*data() const {return _data;}

	allocator_type get_allocator() const { return _alloc;}

	void push_back( const T& value )
	{
		if (_size >= _capacity)
			reserve(_capacity == 0 ? 1 : _capacity * 2);
		_alloc.construct(&_data[_size], value);
		_size++;
	}
	void pop_back()
	{
		_size--;
	}
	reference operator[](size_type idx)
	{
		return _data[idx];
	}
	const_reference operator[](size_type idx ) const
	{
		return _data[idx];
	}
	void reserve(size_type new_size)
	{
		// std::cout << "New size: " << new_size << std::endl;
		if (new_size <= _capacity)
			return;
		if (new_size > max_size())
			throw std::length_error("vector::reserve");
		T *new_addr = _alloc.allocate(new_size);
		for (size_t i = 0; i < _size; i++)
			_alloc.construct(&new_addr[i], _data[i]);
		_alloc.deallocate(_data, _capacity);
		_data = new_addr;
		_capacity = new_size;
	}
	reference  at(size_type pos)
	{
		if (pos >= _size)
			throw std::out_of_range("out of range");
		return (_data[pos]);
	}
	const_reference at(size_type pos) const
	{
		if (pos >= _size)
			throw std::out_of_range("out of range");
		return (_data[pos]);
	}
	void resize( size_type count, T value = T() )
	{
		T *new_addr;
		if (count > _capacity)
			new_addr = _alloc.allocate(count);
		else
			new_addr = _data;
		for (size_t i = 0; _data != new_addr && i < count && i < _size; i++)
			new_addr[i] = _data[i];
		for (size_t i = _size; i < count; i++)
			new_addr[i] = value;
		
		if (_data != new_addr)
		{
			_alloc.deallocate(_data, _capacity);
			_capacity = count;
			_data = new_addr;
		}
		_size = count;
	}


	iterator begin()		{return iterator(_data);}
	iterator end()			{return iterator(_data + _size);}	
	iterator begin() const	{return iterator(_data);}
	iterator end()	const	{return iterator(_data + _size);}

	reverse_iterator rbegin()		{return reverse_iterator(_data + _size - 1);}
	reverse_iterator rbegin() const	{return reverse_iterator(_data + _size - 1);}
	reverse_iterator rend()			{return reverse_iterator(_data - 1);}
	reverse_iterator rend() const	{return reverse_iterator(_data - 1);}

	iterator insert( iterator pos, const T& value )
	{
		insert(pos, 1, value);
		return (pos);
	}

	void insert  ( iterator pos, size_t count, const T& value )
	{
		size_t i_pos = 0;
		if (_data != 0)
			i_pos = &*pos - _data;

		if (_size + count > _capacity)
			reserve(_size == 0 ? count : _size * 2);
		for (size_t i = _size + count; i >= i_pos + count; i--)
			_data[i] = _data[i - count];
		for (size_t i = 0; i < count; i++)
			_data[i_pos + i] = value;
		_size += count;
	}

	template< class InputIt>
	void insert( iterator pos, InputIt first, InputIt last, typename enable_if<!is_integral<InputIt>::value, InputIt>::type* = 0)
	{	
		size_t i_pos = 0;
		if (_data != 0)
			i_pos = &*pos - _data;
		size_t count = distance(first, last);

		// std::cout << "p--------------------------"<< i_pos << " " << count << " " << _size << std::endl;
		if (_size + count > _capacity)
			reserve(_size == 0 ? count : _size * 2);
		for (size_t i = _size + count; i > i_pos + count; i--)
			_data[i] = _data[i - count];
		size_t x = 0;
		for (InputIt it = first; x < count && it != last; x++, it++)
			_alloc.construct(&_data[x + i_pos], *it);
		_size += count;
	}

	iterator erase(iterator pos )
	{
		size_t i = &*pos - _data + 1;
		for (; i < _size; i++)
			_data[i - 1] = _data[i];
		_size--;
		return (pos);
	}

	iterator erase( iterator first, iterator last )
	{
		size_t i = &*first - _data + 1;
		size_t endi = &*last - _data + 1;

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
