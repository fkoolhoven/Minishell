# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/31 14:20:16 by jhendrik          #+#    #+#              #
#    Updated: 2023/09/22 14:02:24 by fkoolhov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
CC			:= cc
RM			:= rm

CFLAGS		?= -Wall -Wextra -Werror #-fsanitize=address
FLAGS		?= -v -Llibs/libft/ -lft -lreadline #-fsanitize=address

INC			:= ./inc/
SRC_DIR		:= src
OBJ_DIR		:= obj
LIB_DIR		:= libs/libft
SUBDIR		:= . \
			   builtins \
			   utils \
			   executer \
			   expander \
			   parser \
			   signals \
			   token
SRC_SUBDIR	:= $(foreach dir, $(SUB_DIR),$(addprefix $(SRC_DIR)/,$(dir)))

SRC			:= main.c \
			   token/token.c \
			   token/token_test.c \
			   token/token_utils.c \
			   token/token_tokenize.c \
			   parser/parser.c \
			   parser/parser_test.c \
			   parser/parser_lists.c \
			   parser/parser_tokens.c \
			   parser/parser_utils.c \
			   expander/expand.c \
			   signals/signals.c \
			   utils/hashnode_functions.c \
			   utils/init_env.c \
			   utils/print_hashtable.c 
OBJ			:= $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
LIBS		:= $(LIB_DIR)/libft.a
MINI_HEADER	:= ./inc/minishell.h


# LIBNAME		:= libft.a

VPATH = $(SRCDIRS)

# Prettifying output
# Reset
Reset="\033[0m"				# Text Reset
# Regular Colors
Green="\033[0;32m"			# Green
Yellow="\033[0;33m"			# Yellow
Blue="\033[0;34m"			# Blue
Light_Blue="\033[1;34m"		# Light Blue

all: make_libs $(NAME)

make_libs: $(LIB_DIR)/obj 

$(LIB_DIR)/obj:
	@$(MAKE) bonus -C $(LIB_DIR)

$(NAME): $(OBJ) $(MINI_HEADER)
	@echo $(Light_Blue) Building program ... $(NAME) $(Reset)
	$(CC)  -I $(INC) $(OBJ) -o $(NAME) $(FLAGS)
	@echo $(Green) Program $(NAME) successfully build $(Reset)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(MINI_HEADER)
	@mkdir -p $(@D)
	@echo $(Light_Blue) Compiling code ... $(Reset)
	$(CC) -I $(INC) $(CFLAGS) -c $< -o $@
	@echo $(Green) Successfully compiled! $(Reset)

$(OBJ_DIR):
	@mkdir $@

clean:
	@if [ -d $(OBJ_DIR) ]; then \
		$(RM) -R $(OBJ_DIR); \
	fi
	@$(MAKE) clean -C $(LIB_DIR)
	@echo $(Yellow) Object directory removed $(Reset)

fclean: clean
	@if [ -f $(NAME) ]; then \
		$(RM) -f $(NAME); \
	fi
	@$(MAKE) fclean -C $(LIB_DIR)
	@echo $(Yellow) Program $(NAME) removed $(Reset)

re: fclean all

.PHONY: all, clean, fclean, re, make_libs
