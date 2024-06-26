NAME = ircserv

SRC_PATH = src/
OBJ_PATH = objs/

SRC = $(wildcard $(SRC_PATH)/*.cpp)
OBJ = $(patsubst $(SRC_PATH)/%.cpp, $(OBJ_PATH)/%.o, $(SRC))

CC = c++
CPPFLAGS = -std=c++98 -Wall -Werror -Wextra

HOSTNAME = $(shell hostname)

HEADERS = -I ./include -D HOST=\"$(HOSTNAME)\"

#//= Colors =//#
BOLD    := \033[1m
BLACK   := \033[30;1m
RED     := \033[31;1m
GREEN   := \033[32;1m
YELLOW  := \033[33;1m
BLUE    := \033[34;1m
MAGENTA := \033[35;1m
CYAN    := \033[36;1m
WHITE   := \033[37;1m
RESET   := \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@ $(CC) $(CPPFLAGS) $(OBJ) $(HEADERS) -o $(NAME)
	@ echo "\n$(GREEN)$(NAME) compiled$(RESET)\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@ mkdir -p  $(OBJ_PATH)
	@ $(CC) $(CPPFLAGS) -c $< -o $@ $(HEADERS) 

clean:
	@ rm -rf $(OBJ_PATH)

fclean: clean
	@ rm -rf $(NAME)
	@ echo "\n$(RED)$(NAME) deleted$(RESET)\n";

re: fclean all

.PHONY: all clean fclean re