#include "tests.hpp"

int main(int argc, char** argv)
{
	#ifdef STD
		std::cout << "STD:\n";
	#else
		std::cout << "FT:\n";
	#endif
	vector_test();
	map_test();
	set_test();
	stack_test();
	return (0);
}
