#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft {
  	template <typename D>
	void swap(D& first, D& second)
	{
		D temp = second;
		second = first;
		first = temp;
	}
}
#endif
