#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

namespace ft
{
	template <class Value, typename NodeBasePtr, typename NodePtr>
	class rbtree_iter;

	template <class Value>
	class vector_iter;

	template <class Iterator>
	class reverse_iterator;

	template <typename Iterator>
	struct iterator_traits {};

	template<typename Value, typename T1, typename T2> 
	struct iterator_traits<ft::rbtree_iter<Value, T1, T2> >
	{
		typedef Value        	value_type;
    	typedef std::size_t   	difference_type;
    	typedef Value*         	pointer;
    	typedef Value&         	reference;
		typedef std::bidirectional_iterator_tag	iterator_category;
	};


	template<typename Value> 
	struct iterator_traits<ft::vector_iter<Value> >
	{
		typedef Value        	value_type;
    	typedef std::size_t   	difference_type;
    	typedef Value*         	pointer;
    	typedef Value&         	reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template <typename T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template <typename T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t					difference_type;
		typedef const T						value_type;
		typedef const T*					pointer;
		typedef const T&					reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template <typename Iterator>
	struct iterator_traits<ft::reverse_iterator<Iterator> >
	{
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
	};
}

#endif
