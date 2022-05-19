CFLAGS = -Wall -Wextra -Werror -Iinclude
CC = gcc

READLINE_LIB 	= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
READLINE_INC	= -I /Users/$(USER)/.brew/opt/readline/include

SRCS = srcs/main.c \
	   srcs/builtins/cd.c \
	   srcs/builtins/echo.c \
	   srcs/builtins/env.c \
	   srcs/builtins/exit.c \
	   srcs/builtins/export.c \
	   srcs/builtins/pwd.c \
	   srcs/builtins/unset.c \

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
