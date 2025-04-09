# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afontele <afontele@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/06 18:35:57 by afontele          #+#    #+#              #
#    Updated: 2025/04/09 11:41:14 by afontele         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the executable
NAME = minishell

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -lreadline

RM = rm -rf
INC = ./inc/minishell.h

# Directories
SRCDIR = src/
OBJDIR = obj/
INCDIR = inc/
LIBFTDIR = libft/

# Sources
SRC = $(SRCDIR)main.c \
		$(SRCDIR)builtins.c \
		$(SRCDIR)builtin_utils.c \
		$(SRCDIR)cd.c \
		$(SRCDIR)env_exp.c \
		$(SRCDIR)pwd_echo_exit_unset.c \
		$(SRCDIR)error.c \
		$(SRCDIR)free.c \
		$(SRCDIR)execve_hub.c \
		$(SRCDIR)pipes.c \
		$(SRCDIR)processes.c \
		$(SRCDIR)redirections.c \
		$(SRCDIR)setup_exec.c \
		$(SRCDIR)heredoc.c \
		$(SRCDIR)env_management.c \
		$(SRCDIR)init.c \
		$(SRCDIR)utils.c \
		
# Objects
OBJ = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRC))
LIBFT = -L $(LIBFTDIR) -lft

# Rules
# Default rule: build everything
all: $(LIBFT) $(NAME)
		@echo "\033[32m[Compilation complete]\033[0m"

# Rule to compile the libft
$(LIBFT):
		@make -C $(LIBFTDIR)

# Rule to compile the executable
$(NAME): $(OBJ)
		@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT) $(LDFLAGS)
		@echo "\033[32m[Executable created]\033[0m"

# Rule to compile the objects
$(OBJDIR)%.o: $(SRCDIR)%.c
		@mkdir -p $(OBJDIR)
		@$(CC) $(CFLAGS) -I $(INCDIR) -o $@ -c $<
		@echo "\033[33m[$@]\033[0m"

# Rule to clean the objects
clean:
		@$(RM) $(OBJDIR)
		@echo "\033[31m[Objects removed]\033[0m"

# Rule to clean everything
fclean: clean
		@$(RM) $(NAME)
		@make -C $(LIBFTDIR) fclean
		@echo "\033[31m[Executable removed]\033[0m"

# Rule to recompile everything
re: fclean all		

.PHONY: all clean fclean re
