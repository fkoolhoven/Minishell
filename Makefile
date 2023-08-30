NAME		= minishell
COMP		= cc
FLAGS		= -Wall -Wextra -Werror
RM			= rm -f
INC			= inc/minishell.h
SRC_DIR		= src
OBJ_DIR		= obj
LIBFT_DIR	= lib/libft
LIBFT		= $(LIBFT_DIR)/libft.a
OBJ			= $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
SRC			= main.c \
				token.c

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	make bonus -C $(LIBFT_DIR)
	$(COMP) -I $(INC) $(LIBFT) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(COMP) $(FLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	$(RM)r $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all