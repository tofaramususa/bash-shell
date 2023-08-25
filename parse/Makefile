NAME = parsing

SRCS = $(wildcard *.c) $(wildcard 1_words_and_operators/*.c) $(wildcard 2_syntax_check_and_expansion/*.c)  $(wildcard 3_s_commands_and_redirs/*.c) $(wildcard array_methods/*.c)
LIBFT_SRCS = $(wildcard Libft/*.c)

CC = gcc -g

CFLAGS = -Wall -Werror -Wextra -Iincludes -fsanitize=address

OBJ = $(SRCS:.c=.o) $(LIBFT_SRCS:.c=.o)

all: $(NAME)

%.o: %.c
		@$(CC) $(CFLAGS) -c $< -o $@
		@echo ......Compiling.......

$(NAME): $(OBJ) Parse.h 
		@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
		@echo .........Compiling Done..............

clean: 
		@rm -rf $(OBJ)
		@echo .........Deleting Object Files..........

fclean: clean
		@rm -f $(NAME)
		@echo ..........Deleting Output Files.........

norm:
		@norminette *.c
		@norminette *.h

re: fclean all

help:
	@echo "....................... <<HELP COMMAND>> ......................................."
	@echo ""
	@echo "make            .........compiles all *.c files"
	@echo "make clean      .........cleans all *.o files"
	@echo "make fclean 	   .........cleans all *.o files and library"
	@echo "make re         .........cleans all files and compiles again"
	@echo "make norm       ..........controls all *.c and *.h codes to norminette standard"
	@echo "                ..........if finds norminette error will break"

.PHONY: all clean fclean re