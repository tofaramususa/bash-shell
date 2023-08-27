NAME = parsing.a

SRCS = $(wildcard *.c) $(wildcard 1_words_and_operators/*.c) $(wildcard 2_syntax_check_and_expansion/*.c)  $(wildcard 3_s_commands_and_redirs/*.c) $(wildcard array_methods/*.c)

CC = cc -g

CFLAGS = -Wall -Werror -Wextra -Iincludes

OBJ = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
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