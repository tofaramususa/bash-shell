NAME = minishell

SRCS = 	main.c\
		garbage_collector.c\
		minishell.c\
		
PARSE_SRCS = parse/1_words_and_operators/ft_space.c\
			parse/1_words_and_operators/ft_strtok.c\
			parse/1_words_and_operators/quotes_methods.c\
			parse/2_syntax_and_expansion/expand_helpers.c\
			parse/2_syntax_and_expansion/expand.c\
			parse/2_syntax_and_expansion/filename_expansion.c\
			parse/2_syntax_and_expansion/quote_removal.c\
			parse/2_syntax_and_expansion/syntax_checks.c\
			parse/2_syntax_and_expansion/token_methods.c\
			parse/3_commands_and_redirs/compound_methods.c\
			parse/3_commands_and_redirs/handle_redirs.c\
			parse/3_commands_and_redirs/smnd_methods.c\
			parse/array_methods/append_array.c\
			parse/array_methods/array_methods.c\
			parse/array_methods/free_methods.c\
			parse/Pipeline.c \

EXECUTION_SRCS = execution/builtins/ft_builtin.c\
				execution/builtins/ft_cd.c\
				execution/builtins/ft_export.c\
				execution/builtins/ft_export_utils.c\
				execution/env/ft_create_env_list.c\
				execution/env/ft_get_env.c\
				execution/env/ft_linkedlist.c\
				execution/env/ft_search.c\
				execution/processes/added.c\
				execution/processes/ft_atoi_modified.c\
				execution/processes/ft_more_cmd_proccess_util.c\
				execution/processes/ft_one_cmd_proccess.c\
				execution/processes/ft_two_more_cmd_proccess.c\
				execution/processes/pipex.c\
				execution/redirections/ft_heredoc.c\
				execution/redirections/ft_red_files_util.c\
				execution/redirections/ft_red_files.c\
				execution/signals.c\

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