#ifndef FT_SWAP_HPP
#define FT_SWAP_HPP

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
