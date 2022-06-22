CFLAGS = -Wall -Wextra -Werror -Iinclude
CC = gcc

READLINE_LIB 	= -lreadline -L /Users/$(USER)/.brew/Cellar/readline/8.1.2/include/readline
READLINE_INC	= -I /Users/$(USER)/.brew/Cellar/readline/8.1.2/lib

SRCS = srcs/main.c \
	   srcs/builtins/cd.c \
	   srcs/builtins/builtin.c \
	   srcs/builtins/echo.c \
	   srcs/builtins/env.c \
	   srcs/builtins/exit.c \
	   srcs/builtins/export.c \
	   srcs/builtins/pwd.c \
	   srcs/builtins/unset.c \   #TODO
	   srcs/env/environment.c \
	   srcs/signals/signals.c \
	   srcs/utils/errors.c \

LIBFT = libft/libft.a

NAME = minishell

OBJS = $(SRCS:.c=.o)

all:  $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(READLINE_INC) $(READLINE_LIB)

$(LIBFT):
	@make -C ./libft

%.o: %.c
	$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@

clean:
	@make clean -C libft/
	@rm -rf $(OBJS)

fclean: clean
	@make fclean -C libft/
	@rm -rf $(NAME) $(OBJS)

re: fclean all
