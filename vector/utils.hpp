#ifndef UTILS_HPP
#define UTILS_HPP

  	template <typename D>
	void ft_swap(D& first, D& second)
	{
		D temp = second;
		second = first;
		first = temp;
	}
#endif
