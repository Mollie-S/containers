# executable names
CONTAINERS = containers
NAME = $(addprefix $(CONTAINERS), _tests)
EXE = $(addprefix ft_, $(NAME))

# directories
SRC_DIR = tests/mandatory_tests
BUILD_DIR = build
BUILD_PATH = $(addprefix $(BUILD_DIR)/, mandatory/ft)
CONTAINERS_INC_DIR = includes

CONTAINERS_HEADERS = map.hpp \
					set.hpp \
					stack.hpp \
					vector.hpp \
					iterator/iterator_traits.hpp \
					iterator/reverse_iterator.hpp \
					red_black_tree/rbtree_iterator.hpp \
					red_black_tree/rbtree_node.hpp \
					red_black_tree/rbtree.hpp \
					utility/enable_if.hpp \
					utility/equal.hpp \
					utility/false_type.hpp \
					utility/ft_swap.hpp \
					utility/is_integral.hpp \
					utility/lexicographical_compare.hpp \
					utility/pair.hpp \
					utility/true_type.hpp

HEADERS = $(addprefix $(SRC_DIR)/, include/tests.hpp)

SRC = main.cpp \
	tests_map.cpp \
	tests_set.cpp \
	tests_stack.cpp \
	tests_vector.cpp

# catch2 tests
ifdef catch
	EXE = $(addprefix catch2_, $(NAME))
	SRC_DIR = tests/catch2_tests

	SRC = catch_main.cpp \
	catch_map_test.cpp \
	catch_set_test.cpp \
	catch_stack_test.cpp \
	catch_vector_test.cpp

	HEADERS = $(addprefix $(SRC_DIR)/, include/catch.hpp) 
	BUILD_PATH = $(addprefix $(BUILD_DIR)/, catch2)
	CXXFLAGS = -I$(CONTAINERS_INC_DIR) -std=c++11 \
			-g -fsanitize=address
else
	CXXFLAGS = -Wall -Wextra -Werror \
			-I$(CONTAINERS_INC_DIR) \
			-std=c++98 -pedantic \
			-g -fsanitize=address -O3
endif

# for compiling with std namespace 
ifdef STD
	EXE = $(addprefix std_, $(NAME))
	BUILD_PATH = $(addprefix $(BUILD_DIR)/, mandatory/std)
	CXXFLAGS += -D=STD
endif


CONTAINERS_HEADERS := $(addprefix $(CONTAINERS_INC_DIR)/,$(CONTAINERS_HEADERS))
OBJ = $(SRC:.cpp=.o)
CXX=clang++

.PHONY: all clean fclean re std catch

all: $(EXE)

$(EXE): $(addprefix $(BUILD_PATH)/,$(OBJ))
	$(CXX) -o $(addprefix $(BUILD_DIR)/, $(EXE)) $(CXXFLAGS) $(addprefix $(BUILD_PATH)/,$(OBJ))

$(BUILD_PATH)/%.o: $(SRC_DIR)/%.cpp $(HEADERS) $(CONTAINERS_HEADERS)
	mkdir -p ${dir $@}
	$(CXX) $(CXXFLAGS) -c -o $@ $<

std:
	$(MAKE) STD=1 all

catch:
	$(MAKE) catch=1 all

clean:
	rm -rf $(BUILD_DIR)

re:
	$(MAKE) fclean
	$(MAKE) all
