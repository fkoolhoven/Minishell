# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/31 14:20:16 by jhendrik          #+#    #+#              #
#    Updated: 2023/08/31 16:39:21 by fkoolhov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
CC			:= cc
RM			:= rm

CFLAGS		?= -Wall -Wextra -Werror
FLAGS		?= -lreadline

INC			:= ./inc/
SRC_DIR		:= src
OBJ_DIR		:= obj
LIB_DIR		:= libs/libft
SUBDIR		:= . \
			   builtins \
			   utils
SRC_SUBDIR	:= $(foreach dir, $(SUB_DIR),$(addprefix $(SRC_DIR)/,$(dir)))

SRC			:= main.c token.c token_utils.c token_tokenize.c
OBJ			:= $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
LIBS		:= $(LIB_DIR)/libft.a
MINI_HEADER	:= ./inc/minishell.h

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
	$(CC) $(FLAGS) $(LIBS) -I $(INC) $(OBJ) -o $(NAME)
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
