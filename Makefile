# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: felicia <felicia@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/31 14:20:16 by jhendrik          #+#    #+#              #
#    Updated: 2024/03/03 22:08:09 by felicia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell
CC			:= cc
RM			:= rm

CFLAGS		?= -Wall -Wextra -Werror -g
FLAGS		?= -v -Llibs/libft/ -lft -lreadline

INC			:= ./inc/
SRC_DIR		:= src
OBJ_DIR		:= obj
LIB_DIR		:= libs/libft
SUBDIR		:= . \
			   builtins \
			   utils \
			   executer \
			   parser \
			   signals \
			   token \
			   expander \
			   env_functions \
			   errors
SRC_SUBDIR	:= $(foreach dir, $(SUB_DIR),$(addprefix $(SRC_DIR)/,$(dir)))

SRC			:= main.c \
			   errors/errors_parser.c \
			   errors/errors_exec_swap.c \
			   errors/errors_exec_process.c \
			   token/token.c \
			   token/token_utils.c \
			   token/token_tokenize.c \
			   token/token_quotes.c \
			   token/token_terminate.c \
			   expander/expand.c \
			   expander/expand_variable.c \
			   expander/expand_split_value.c \
			   expander/expand_update.c \
			   expander/expand_split_token.c \
			   expander/expand_replace.c \
			   expander/expand_concatenate.c \
			   expander/expand_update_utils.c \
			   expander/expand_remove_empty.c \
			   parser/parser.c \
			   parser/parser_parse_token.c \
			   parser/parser_command_list.c \
			   parser/parser_redirect_list.c \
			   parser/parser_bools.c \
			   parser/parser_terminate.c \
			   signals/signals.c \
			   signals/sig_wrapper.c \
			   executer/heredoc_handler.c \
			   executer/heredoc_unlinker.c \
			   executer/heredoc_utils.c \
			   executer/input_heredoc.c \
			   executer/manage_one_heredoc.c \
			   executer/heredoc_bool.c \
			   executer/heredoc_expandinput.c \
			   executer/exec.c \
			   executer/exec_builtins.c \
			   executer/exec_one_cmnd.c \
			   executer/exec_utils.c \
			   executer/swap_fds.c \
			   executer/give_fds.c \
			   executer/processes.c \
			   executer/valid_path.c \
			   executer/terminate_execvar.c \
			   executer/close_fds.c \
			   executer/swap_fd_mini.c \
			   utils/hashnode_functions.c \
			   utils/hashnode_add_delete.c \
			   utils/process_add_delete.c \
			   utils/process_functions.c \
			   env_functions/env_terminate.c \
			   env_functions/env_utils.c \
			   env_functions/init_env.c \
			   env_functions/init_keyvalue_pairs.c \
			   env_functions/add_delete_pair.c \
			   env_functions/find_key.c \
			   env_functions/split_first_occurance.c \
			   env_functions/convert_to_strarray.c \
			   env_functions/convert_utils.c \
			   builtins/cd.c \
			   builtins/cd_abspath.c \
			   builtins/cd_curpath.c \
			   builtins/cd_edit_path.c \
			   builtins/cd_prev.c \
			   builtins/cd_strtrim.c \
			   builtins/cd_strtrim_utils.c \
			   builtins/cd_utils.c \
			   builtins/cd_change_env.c \
			   builtins/echo.c \
			   builtins/echo_optioncheck.c \
			   builtins/env.c \
			   builtins/exit.c \
			   builtins/export.c \
			   builtins/export_value.c \
			   builtins/pwd.c \
			   builtins/unset.c
OBJ			:= $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
LIBS		:= $(LIB_DIR)/libft.a
MINI_HEADER	:= ./inc/minishell.h

VPATH = $(SRCDIRS)

#COLORS
Reset="\033[0m"
Green="\033[0;32m"			
Yellow="\033[0;33m"		
Blue="\033[0;34m"		
Light_Blue="\033[1;34m"	

all: make_libs $(NAME)

make_libs: $(LIB_DIR)/obj 

$(LIB_DIR)/obj:
	@$(MAKE) bonus -C $(LIB_DIR)

$(NAME): $(OBJ) $(MINI_HEADER)
	@echo $(Light_Blue) Building program ... $(NAME) $(Reset)
	@$(CC)  -I $(INC) $(OBJ) -o $(NAME) $(FLAGS)
	@echo $(Green) Program $(NAME) successfully build $(Reset)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(MINI_HEADER)
	@mkdir -p $(@D)
	@$(CC) -I $(INC) $(CFLAGS) -c $< -o $@

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
