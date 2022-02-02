#ifndef TRUE_TYPE_HPP
#define TRUE_TYPE_HPP

namespace ft
{
	struct true_type {
		static const bool value = true;
		operator bool() const
		{ 
			return value;
		}
	};
}

#endif
