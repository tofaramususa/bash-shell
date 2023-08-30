NAME = minishell

SRCS = $(wildcard *.c)
PARSE_SRCS = $(wildcard parse/*.c) $(wildcard parse/1_words_and_operators/*.c) $(wildcard parse/2_syntax_check_and_expansion/*.c)  $(wildcard parse/3_simple_commands_and_redirs/*.c) $(wildcard parse/array_methods/*.c)
EXECUTION_SRCS = $(wildcard execution/*.c) $(wildcard execution/builtins/*.c) $(wildcard execution/env_variables_list/*.c) $(wildcard execution/pipes_and_processes/*.c)  $(wildcard execution/redirections/*.c)

CC = cc
CFLAGS = -Wall -Werror -Wextra -IIncludes
LDFLAGS = -Llibft -lft

OBJ = $(SRCS:.c=.o) $(PARSE_SRCS:.c=.o) $(EXECUTION_SRCS:.c=.o)

all: $(NAME)

%.o: %.c Includes/minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

Libft/libft.a:
	$(MAKE) -C Libft

$(NAME): $(OBJ) Libft/libft.a
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS) -lreadline

mm:
	valgrind --trace-children=yes --show-leak-kinds=all --leak-check=full --show-reachable=yes --track-fds=yes --error-limit=no --suppressions=readline.supp ./minishell
	# valgrind --trace-children=yes --show-leak-kinds=all --leak-check=full --show-reachable=yes --track-fds=yes --error-limit=no ./minishell

clean: 
	rm -rf $(OBJ)

fclean: clean
	$(MAKE) fclean -C Libft
	rm -f $(NAME)

norm:
	norminette *.c
	norminette *.h

re: fclean all

.PHONY: all clean fclean re norm