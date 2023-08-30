NAME		= minishell
COMP		= cc
FLAGS		= -Wall -Wextra -Werror
RM			= rm -f
INC			= inc/minishell.h
SRC_DIR		= src
OBJ_DIR		= obj
OBJ			= $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
SRC			= main.c \

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	$(COMP) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(COMP) $(FLAGS) -c $< -o $@

clean:
	$(RM)r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all