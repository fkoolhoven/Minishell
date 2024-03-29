# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                          :+:    :+:              #
#                                                     +:+ +:+         +:+      #
#    By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/28 10:58:27 by jhendrik          #+#    #+#              #
#    Updated: 2023/11/03 14:21:28 by jhendrik      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CC := cc

# Defining directories
SRCDIR := ./src
OBJDIR := ./obj

SUBDIRS = functions_chars functions_str functions_mem functions_conversion functions_outputfd functions_lnklist
SRCDIRS = $(foreach dir,$(SUBDIRS),$(addprefix $(SRCDIR)/,$(dir)))
OBJDIRS = $(foreach dir,$(SUBDIRS),$(addprefix $(OBJDIR)/,$(dir)))

# Add the SRCDIRS to VPATH so make knows where to find the srcfiles 
VPATH = $(SRCDIRS)

# Name of final archive
NAME := libft.a

# Defining files
HEADERS := -I ./include 
HEADERLIBFT := ./include/libft.h
SRCFILES := functions_chars/ft_isalpha.c \
			functions_chars/ft_isdigit.c \
			functions_chars/ft_isalnum.c \
			functions_chars/ft_isascii.c \
			functions_chars/ft_isprint.c \
			functions_chars/ft_tolower.c \
			functions_chars/ft_toupper.c \
			functions_chars/ft_isspace.c \
			functions_str/ft_strlen.c \
			functions_str/ft_strlcpy.c \
			functions_str/ft_strlcat.c \
			functions_str/ft_strchr.c \
			functions_str/ft_strrchr.c \
			functions_str/ft_strncmp.c \
			functions_str/ft_strnstr.c \
			functions_str/ft_strdup.c \
			functions_str/ft_substr.c \
			functions_str/ft_strjoin.c \
			functions_str/ft_strtrim.c \
			functions_str/ft_split.c \
			functions_str/ft_strmapi.c \
			functions_str/ft_striteri.c \
			functions_str/ft_free_str_array.c \
			functions_mem/ft_memset.c \
			functions_mem/ft_bzero.c \
			functions_mem/ft_memcpy.c \
			functions_mem/ft_memmove.c \
			functions_mem/ft_memchr.c \
			functions_mem/ft_memcmp.c \
			functions_mem/ft_calloc.c \
			functions_conversion/ft_itoa.c \
			functions_conversion/ft_atoi.c \
			functions_conversion/ft_itoa_base.c \
			functions_conversion/ft_luitoa_base.c \
			functions_outputfd/ft_putchar_fd.c \
			functions_outputfd/ft_putlui_base.c \
			functions_outputfd/ft_putnbr_base.c \
			functions_outputfd/ft_putstr_fd.c \
			functions_outputfd/ft_putendl_fd.c \
			functions_outputfd/ft_putnbr_fd.c \
			functions_outputfd/ft_putstr_array_fd.c
SRCFILES_BONUS := functions_lnklist/ft_lstnew_bonus.c \
				functions_lnklist/ft_lstadd_front_bonus.c \
				functions_lnklist/ft_lstsize_bonus.c \
				functions_lnklist/ft_lstlast_bonus.c \
				functions_lnklist/ft_lstadd_back_bonus.c \
				functions_lnklist/ft_lstdelone_bonus.c \
				functions_lnklist/ft_lstclear_bonus.c \
				functions_lnklist/ft_lstiter_bonus.c \
				functions_lnklist/ft_lstmap_bonus.c 
OBJFILES := $(addprefix $(OBJDIR)/,$(SRCFILES:.c=.o))
OBJFILES_BONUS := $(addprefix $(OBJDIR)/,$(SRCFILES_BONUS:.c=.o))

# Defining flags
CFLAGS ?= -Wall -Werror -Wextra

ifdef BONUS
	OBJFILES += $(OBJFILES_BONUS)
endif

# Prettifying output by defining colours
# Reset
Reset="\033[0m"			# Text Reset

# Regular Colours
Black="\033[0;30m"			# Black
Red="\033[0;31m"			# Red
Green="\033[0;32m"			# Green
Yellow="\033[0;33m"			# Yellow
Blue="\033[0;34m"			# Blue
Light_Blue="\033[1;34m"		#Light Blue
Purple="\033[0;35m"			# Purple
Cyan="\033[0;36m"			# Cyan
White="\033[0;37m"			# White

# Bold text style
Bold="\033[1m"

all: $(NAME)

$(NAME): $(OBJFILES)
	@$(AR) -rsc $@ $^
	@echo $(Green) Made $(NAME) succesfully! $(Reset)

bonus:
	@$(MAKE) BONUS=1 all


$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERLIBFT) | $(OBJDIR)
	@mkdir -p $(@D)
	@$(CC) -c $(CFLAGS) $(HEADERS) $<
	@mv ./$(notdir $@) $(@D)	

$(OBJDIR):
	@mkdir $@

clean:
	@if [ -d $(OBJDIR) ]; then \
		rm -R $(OBJDIR); \
	fi

fclean: clean
	@if [ -f $(NAME) ]; then \
		rm -f $(NAME); \
	fi

re: fclean all

.PHONY: all, clean, fclean, re, bonus
