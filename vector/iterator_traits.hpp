#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

// The reason to use != rather than < for testing 
// whether we have reached the end is partially because
// that is the more precise statement of what we are testing for 
// and partially because only randomaccess iterators support <. (Stroupstrup)

namespace ft {
// 	struct input_iterator_tag {};
// 	struct output_iterator_tag {};
// 	struct forward_iterator_tag : public input_iterator_tag {};
// 	struct bidirectional_iterator_tag : public forward_iterator_tag {};
// 	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
// 
// 
// 	template<typename T>
// 	is_iterator : public integral_constant<bool, !is_integral<T>::value>{};
// 
// 	template<typename T, T v>
// 	struct integral_constant {
// 		static const T value = v;
// 		typedef T value_type;
// 		typedef integral_constant type; // using injected-class-name
// 		const operator value_type() const { return value; }
// 	};
// 
// 	template <typename T>
// 	struct is_iterator
// 	{
// 	private:
// 		typedef char	true_type;
// 		typedef int		false_type;
// 
// 		template <typename U>
// 		static true_type test(typename U::iterator_category* = 0);
// 		template <typename U>
// 		static false_type test(...);
// 
// 	public:
// 		static const bool result = (sizeof(true_type) == sizeof(test<T>(0)));
// 	};
// 
// 	template <class Iterator, bool>
// 	struct _iterator_traits {};





// IS IT CORRECT???::
template <class Iter, bool>
struct _iterator_traits
{
};

	template <typename Iter>
	struct iterator_traits : public enable_if<is_iterator<Iter::value_type>::result, T>
	{
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template < class Iterator>
	struct _iterator_traits<Iterator, true>
	{
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <typename T>
	struct iterator_traits : public enable_if<is_iterator<T>::result, T>
	{
		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template <typename T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;

	};

	template <typename T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t					difference_type;
		typedef const T						value_type;
		typedef const T*					pointer;
		typedef const T&					reference;
		typedef random_access_iterator_tag	iterator_category;

	};
}

#endif
