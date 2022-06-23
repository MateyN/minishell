# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmamison <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/14 18:02:56 by rmamison          #+#    #+#              #
#    Updated: 2022/06/16 19:04:13 by rmamison         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft

SRC = main.c \
	builtins/builtin.c \
	builtins/echo.c \
	builtins/cd.c \
	builtins/env.c \
	builtins/exit.c \
	builtins/pwd.c \
	env/environment.c \
	signals/signals.c \
	utils/errors.c \
	
SRCS = $(addprefix srcs/, $(SRC))

INCLUDE = -I includes/ -I libft/
		  #-I ~/.brew/Cellar/readline/8.1.2/include/readline

READLINE_LIB = -L /Users/$(USER)/.brew/Cellar/readline/8.1.2/lib -lreadline
LIB_LIBFT = libft/libft.a

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
CC = gcc

RM = rm -rf

DIR = file_object
OB = $(addprefix $(DIR)/, $(SRCS:%.c=%.o))
CLONE = file_object \
	file_object/srcs \
	file_object/srcs/builtins \
	file_object/srcs/env \
	file_object/srcs/signals \
	file_object/srcs/utils \

$(DIR)/%.o : %.c
	@echo "Compiling libft..."
	@make -C $(LIBFT)
	@echo "Compilation is done!"
	@mkdir -p $(CLONE)
	@echo "Creating file_object..."
	@$(CC) $(INCLUDE) -c $< -o $@
	@echo "File_object created!"

all : $(NAME)

$(NAME) : $(OB)
	@echo "Compiling..."
	@$(CC) $(FLAGS) $(READLINE_LIB) $(OB) -o $@ libft/libft.a
	@echo "Compilation is done!"

clean :
	@echo "Remove all file_object..."
	@$(RM) $(DIR)
	@make clean -C $(LIBFT)
	@echo "file_object removed!"

fclean : clean
	@echo "Remove all file_object & file_binary..."
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT)
	@echo "object and binary_file removed!"

re : fclean $(NAME)
.PHONY: all clean fclean re
