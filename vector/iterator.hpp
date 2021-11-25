#ifndef ITERATOR_HPP
#define ITERATOR_HPP


				// iterators
		iterator begin(){ return iterator(_elements); } // No-throw guarantee: this member function never throws exceptions.The copy construction or assignment of the returned iterator is also guaranteed to never throw.
		const_iterator begin() const { return const_iterator(_elements); }

		iterator end() { return iterator(_elements + _size); }
		const_iterator end() const { return const_iterator(_elements + _size); }

		reverse_iterator rbegin() { return reverse_iterator (end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

		reverse_iterator rend() { return reverse_iterator (begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator (begin()); }
#endif
