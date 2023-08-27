NAME = execution.a

SRCS = $(wildcard builtins/*.c) $(wildcard env_variables_list/*.c) $(wildcard pipes_and_processes/*.c)  $(wildcard redirections/*.c) $(wildcard *.c)

CC = cc -I/usr/local/Cellar/readline/8.1/include

CFLAGS = -Wall -Werror -Wextra -Iincludes

OBJ = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) minishell.h libft.h
		ar rcs $(NAME) $(OBJ)

clean: 
		rm -rf $(OBJ)

fclean: clean
		rm -f $(NAME)

norm:
		norminette *.c
		norminette *.h

re: fclean all

.PHONY: all clean fclean re