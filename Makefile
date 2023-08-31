NAME = minishell

SRCS = $(wildcard *.c)

CC = cc
CFLAGS = -Wall -Werror -Wextra -Iincludes
LDFLAGS = -Llibft -lft -Lparse -lparse -Lexecution -lexecution

OBJ = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

Libft/libft.a:
	$(MAKE) -C Libft

parse/parse.a:
	$(MAKE) -C parse

execution/execution.a:
	$(MAKE) -C execution

$(NAME): $(OBJ) Libft/libft.a parse/parse.a execution/execution.a 
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS) -lreadline
clean: 
	rm -rf $(OBJ)

fclean: clean
	$(MAKE) fclean -C Libft
	$(MAKE) fclean -C parse
	$(MAKE) fclean -C execution
	rm -f $(NAME)

norm:
	norminette *.c
	norminette *.h

re: fclean all

.PHONY: all clean fclean re norm