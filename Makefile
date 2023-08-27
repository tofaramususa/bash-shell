NAME = minishell

SRCS = $(wildcard *.c)

CC = cc
CFLAGS = -Wall -Werror -Wextra -Iincludes
LDFLAGS = -Llibft -lft -Lparse -lparse -Lexecution -lexecution

OBJ = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(MAKE) -C Libft
	$(MAKE) -C parse
	$(MAKE) -C execution
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

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