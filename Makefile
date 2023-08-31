# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jhendrik <marvin@42.fr>                      +#+                      #
#                                                    +#+                       #
#    Created: 2023/08/30 16:35:33 by jhendrik      #+#    #+#                  #
#    Updated: 2023/08/31 13:08:19 by jhendrik      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
COMP		:= cc
CFLAGS		?= -Wall -Wextra -Werror -g
RM			:= rm -f
INC			:= inc/minishell.h
SRC_DIR		:= src
OBJ_DIR		:= obj
SUB_DIR		:= . \
			   builtins \
			   test_utils \
			   utils
SRC_SUBDIR	:= $(foreach dir,$(SUBDIRS),$(addprefix $(SRCDIR)/,$(dir)))
SRC			:= main.c \
			   test_utils/ft_strlen.c \
			   test_utils/ft_strnstr.c \
			   test_utils/ft_strdup.c \
			   test_utils/ft_strjoin.c
OBJ			:= $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
VPATH		:= $(SRC_SUBDIR)

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	$(COMP) -I $(INC) $(OBJ) -lreadline -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC)
	mkdir -p $(@D)
	$(COMP) -I $(INC) $(CFLAGS) -c $< -o $@

clean:
	$(RM)r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
