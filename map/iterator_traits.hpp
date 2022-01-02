#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

namespace ft
{
	template <class Value, typename NodeBasePtr, typename NodePtr>
	class map_iter;
}

namespace ft {
	template <typename Iterator>
	struct iterator_traits {
	};

	template<typename Value, typename T1, typename T2> 
	struct iterator_traits<ft::map_iter<Value, const T1*, const T2*> >
	{
		typedef Value        	value_type;
    	typedef std::size_t   	difference_type;
    	typedef const Value*    pointer;
    	typedef const Value&    reference;
	};

	template<typename Value, typename T1, typename T2> 
	struct iterator_traits<ft::map_iter<Value, T1*, T2*> >
	{
		typedef Value        	value_type;
    	typedef std::size_t   	difference_type;
    	typedef Value*         	pointer;
    	typedef Value&         	reference;
	};
}

#endif
