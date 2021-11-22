#ifndef FALSE_TYPE_HPP
#define FALSE_TYPE_HPP

namespace ft
{
	struct false_type {
		static const bool value = false;
		operator bool() const { return value;}
	};
}

#endif
