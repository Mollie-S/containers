# executable names
CONTAINERS = containers
NAME = $(addprefix $(CONTAINERS), _tests)
EXE = $(addprefix ft_, $(NAME))

# directories
SRC_DIR = tests/mandatory_tests
BUILD_DIR = build
BUILD_PATH = $(addprefix $(BUILD_DIR)/, mandatory/ft)
INC_DIR = includes/

# catch2 tests
ifdef catch
	EXE = $(addprefix catch2_, $(NAME))
	SRC_DIR = tests/catch2_tests
	BUILD_PATH = $(addprefix $(BUILD_DIR)/, catch2)
	CXXFLAGS = -I$(INC_DIR) -std=c++11 \
			-g -fsanitize=address
else
	CXXFLAGS = -Wall -Wextra -Werror \
			-I$(INC_DIR) \
			-std=c++98 -pedantic \
			-g -fsanitize=address -O3
endif

# for compiling with std namespace 
ifdef STD
	EXE = $(addprefix std_, $(NAME))
	BUILD_PATH = $(addprefix $(BUILD_DIR)/, mandatory/std)
	CXXFLAGS += -D=STD
endif


OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_PATH)/%.o,$(wildcard $(SRC_DIR)/*.cpp))
CXX=clang++

.PHONY: all clean fclean re

all: $(EXE)
	$(MAKE) -j4 $(EXE)

$(EXE): $(OBJ)
	$(CXX) -o $(addprefix $(BUILD_DIR)/, $(EXE)) $(CXXFLAGS) $(OBJ) 

$(BUILD_PATH)/%.o: $(SRC_DIR)/%.cpp
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
