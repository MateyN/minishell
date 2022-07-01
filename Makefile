# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/14 18:02:56 by rmamison          #+#    #+#              #
#    Updated: 2022/07/01 12:24:32 by mnikolov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft

SRC =	main.c \
	builtins/builtin.c \
	builtins/echo.c builtins/cd.c \
	builtins/env.c builtins/exit.c \
	builtins/pwd.c env/environment.c \
	builtins/export.c env/utils.c \
	builtins/export_utils.c \
	signals/signals.c utils/errors.c \
	jud/check_input.c \
	jud/lexical_split.c \
	
SRCS = $(addprefix srcs/, $(SRC))
DIR_S = srcs

INCLUDE = -I includes/ -I libft/ -I /Users/$(USER)/.brew/opt/readline/include/readline

READLINE_LIB = -L /Users/$(USER)/.brew/opt/readline/lib -lreadline
LIB_LIBFT = libft/libft.a

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
CC = clang

RM = rm -rf

DIR = file_object
OB = $(addprefix $(DIR)/, $(SRCS:%.c=%.o))
CLONE = file_object \
	file_object/srcs \
	file_object/srcs/builtins \
	file_object/srcs/env \
	file_object/srcs/signals \
	file_object/srcs/utils \
	file_object/srcs/jud \

$(DIR)/%.o : %.c
	@mkdir -p $(CLONE)
	@$(CC) $(INCLUDE) -c $^ -o $@

all : $(NAME)

$(NAME) : $(OB)
	@echo "Compiling libft..."
	@make -C $(LIBFT)
	@echo "compilation [libft] is done!"
	@echo "Compiling minishell..."
	@$(CC) $(FLAGS) $(READLINE_LIB) $(OB) -o $@ libft/libft.a
	@echo "Compilation [minishell] is done!"

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
