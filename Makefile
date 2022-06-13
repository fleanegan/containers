NAME = Containers
TEST_NAME = $(NAME)_test

# Paths

SRC_PATH = ./src/
OBJ_PATH = ./obj/
TEST_PATH = ./test/

# Names

SRC_NAME =	main.cpp\
			test.cpp\

OBJ_NAME = $(SRC_NAME:.cpp=.o)

TEST_SRC_NAME =	test_main.cpp \

TEST_HEADER_NAME =	testUtils.hpp \
					testIterators.hpp

# Files
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
DEP_NAME := $(patsubst %.o,%.d,$(OBJ))
TEST_SRC = $(addprefix $(TEST_PATH),$(TEST_SRC_NAME))
TEST_HEADER = $(addprefix $(TEST_PATH), $(TEST_HEADER_NAME))
TEST_OBJ_NAME = $(TEST_SRC_NAME:.cpp=.o)
TEST_OBJ = $(addprefix $(OBJ_PATH),$(TEST_OBJ_NAME))
TEST_DEP_NAME := $(patsubst %.o,%.d,$(TEST_OBJ))
OBJ_NO_MAIN := $(filter-out $(OBJ_PATH)main.o, $(OBJ))

# Flags
CXX = c++
CPPFLAGS = -Wall -Wextra -Werror -g -std=c++98
MAKE_DEP_FLAGS = -MMD
TEST_FLAGS	= -pthread -lgtest

ifeq ($(MAKECMDGOALS),test)
	CPPFLAGS += -g -D TESTING
endif

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CPPFLAGS) -I$(SRC_PATH) $(MAKE_DEP_FLAGS) -c $< -o $@

$(OBJ_PATH)%.o: $(TEST_PATH)%.cpp
	@mkdir -p $(@D)
	$(CXX) -D TESTING -I$(TEST_PATH) -I$(SRC_PATH) $(MAKE_DEP_FLAGS) -c $< -o $@

clean:
	@echo "Delete $(OBJ_PATH)"
	@rm -rf $(OBJ_PATH) db

fclean:	clean
	@echo "Delete $(NAME)"
	@rm -f $(NAME) db

$(NAME): $(OBJ)
	@echo "Build $(NAME)"
	@$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME)

test: $(TEST_NAME)

$(TEST_NAME): $(OBJ_NO_MAIN) $(TEST_OBJ)
	$(CXX) -D TESTING $(OBJ_NO_MAIN) $(TEST_OBJ) $(TEST_FLAGS) -I./$(SRC_PATH) -I./$(TEST_PATH) $(TEST_FLAGS) -lm -o $(TEST_NAME)

-include $(DEP_NAME)
-include $(TEST_DEP_NAME)

re:	fclean all

.PHONY: all clean fclean re mlx libft db
