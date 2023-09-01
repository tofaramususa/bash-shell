/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:29:12 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/31 20:31:19 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include <dirent.h>

/*Quotes Struct*/
typedef struct s_quote
{
	bool			single_q;
	bool			double_q;
}					t_quote;

/*Tokens Struct*/
typedef enum
{
	WORD,
	REDIR,
	PIPE,
	AND, 
	OR,
	OPEN_PAREN,
	CLOSE_PAREN,
}					token_type;

typedef enum
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC,
}					t_redir_type;

typedef struct s_char
{
	char **array;
	bool isfreed;
}	t_char;

typedef struct s_token
{
	token_type		type;
	char			*value;
	bool			isfreed;
	struct s_token	*next;
}	t_token;

/*Simple Command and Redirections Struct*/

typedef struct s_redir
{
	t_redir_type	type;
	char			*filename;
	bool			isfreed;
	struct s_redir	*next;
}					t_redir;

typedef struct s_command
{
	char			*cmd;
	int				cmd_len; //assign later this may need adjustment
	int				args_len;
	t_char			*args;
	int				total_redirs; //this will need adjustment
	t_redir			*redirs; //this will need adjust
	bool			isfreed;
}					t_command;

typedef enum
{
	AFTER_OPEN_PAREN,
	BEFORE_CLOSE_PAREN,
	NOT_PAREN,
	
}				t_paren_type;


typedef struct s_compound
{
	t_command **s_commands;
	token_type		split_on;
	int				cmd_len; //update this everywhere
	t_paren_type	paren;
} t_compound;

typedef struct s_shell
{
	t_compound		**cmpd_node; //update this everywhere
	t_char			*env_vars;
	t_list			*env_list;
	int				error_no;
	int				total_pipes; //update this for each command
	char			pwd[1024];
	int				fd[256][2];
	int				pid1;
	int				pid2;
	int				middle_scommand;
	int				scommand_index;
	int				counter;
	int process_id; // id1
	int				process_id1;
	char			*line;
	t_token			*tokenlist;
	t_list			*temp_list;
	int				flag;
	int				flag_out;
	int				flag_in;
	int				check;
	int				x;
	int				dont;
	unsigned long long copy; //for ft_exit_helper
	bool			isfreed;
}					t_shell;

typedef struct s_heredoc_var // structure for heredoc
{
	int file1;       // thinking file descriptor
	char *tmp;       // not sure
	char *delimiter; // not sure
	int ret;         // not sure
} t_heredoc_var;     // not sure

typedef struct s_exp_var
{
	char			*cp;
	char			*tmp;
	char			*tmp_ex;
	int				x;
	int				y;
	int				start;
	int				flag_sq;
	int				flag_dq;
	int				flag_pwd;
	int				flag_shlvl;
	int				flag_oldpwd;
	int				flag;
	int				last_index;
	int				last_pos;
	t_list			*tmp_list;

} t_exp_var; // this may be about expansion variables
/*PARSING*/
/*Array Methods*/

extern int			g_error_status;
void				free_array(char **array);
void				free_t_char(t_char **array);
int					ft_array_len(char **str);
bool				array_strchr(char *s, char c);
char				**dup_array(char **array);
bool				check_line(char *str);
char				**append_array(char **s1, char **s2);
t_char				*linked_to_array(t_list *head);

/*Quote Methods*/
bool				check_unmatched_quotes(char *str);
void				set_quote_flag(t_quote *value, char c);
char				*remove_quotes(char *str);
void				token_quote_removal(t_token *tokenlist);

/*Words and Operators*/
char				**ft_space(char *s);
char				**ft_strtok(char *s);
char				**ft_split_on_delims(char *str);
t_token				*ft_tokenise(t_shell *bash, char **tokens);
t_token				*create_token_list(char **tokens);
void				free_token_list(t_token **tokenlist);

/*Syntax Check and Expansion*/
bool				token_syntax_check(t_token *headToken);
char				*final_expanded_str(t_shell *bash, char *str);
bool				needs_expansion(char *str);
int					get_search_var_end(char *str, int start);
int					get_end_index_expan(char *str, int start);
char				*strjoin_new_var(char *temp_str, char *expanded_str,
						int count);
char				**expand_array(t_shell *bash, char **str);
t_token	*new_token_node(char *arg);
void	add_token_node(t_token **tokenlist, t_token *tokenNode);
bool filename_expansion(t_token *tokenlist, char *str_token);

/*Simple Commands and Redirections*/
t_command			*create_scmnd_node(t_token *start, t_token *end);
t_compound *create_compound_node(t_token *start, t_token *end);
void				fill_scmnd(t_command *scommand, t_token *start,
						t_token *end);
void				fill_redirs(t_command *scommand, t_token *redir,
						t_token *filename);
void				free_redirs_list(t_redir **redirlist);

/*Debugging*/
void				print_array(char **str);
// void				// write_to_debugfile(char *str);
// void // write_to_funcfclearile(char *str);
void			print_tokens(t_token *tokens);
void print_scommands(t_command **simpleCmnds);

/*EXECUTION*/
int	pipex(int ac, t_command **scommand, t_shell *bash);
void	garbage_collector(t_shell **bash);
void 	safe_free(void  *ptr);
int	check_nns(char *str);
char	*get_command(t_shell *proc, char **envp, char *s);
void	cmd_not_found(t_command **av, t_shell *proc, int counter);

/*BUILTINS*/
void	ft_echo(t_command **pipe, t_shell *proc);
int	ft_exit_helper(const char *str, t_shell *proc);
void	ft_pwd(t_shell *data);
int	ft_validate_export(char *str);
void	print_and_set_flag(t_command **pipe, t_shell *proc);
void	check_built_ins_and_exexute_one_cmd(t_shell *proc, t_command **av,
		char **envp);
void	check_built_ins_and_exexute(t_shell *proc, t_command **av, char **envp);
void	ft_exit(t_command **pipe, t_shell *proc);
int	ft_cd(t_command **pipe, t_shell *proc);
void	ft_env_print_linked(t_shell *proc);
int	ft_unset(t_command **pipe, t_shell *proc);
int	ft_check_builtin(char *cmd);
void	child_sig_handler(int num);
void	do_operation(t_shell *proc, t_command **av);


/*Environment Variables Functions*/
void	create_envlist(t_shell *proc, char **env);
char	*ft_getenv(t_list *head, char *str);
int	check_and_replace(t_list *head, char *replace);
void	sort_list(t_list *head);
void	re_index(t_list *head);
int	remove_element(t_list **head, int index);
void	ft_env_print_linked(t_shell *proc);
int	ft_export_to_linked(t_command **pipe, t_shell *prc);
int	ft_export_print_linked(t_command **pipe, t_shell *prc);
int	search_for_path(char **envp);


/*SIGNALS*/ 
void	sig_handler(int num);
void init_signals(void);

/*REDIRECTIONS*/ 
int	check_and_update_heredoc(t_command **s_commands, t_shell *bash);
void	red_one_cmd(t_command **av, t_shell *proc);
void	red_first_proc(t_command **av, int *flag, t_shell *proc);
void	red_middle(t_command **av, int *flag_out, int *flag_in, t_shell *proc);
void	red_last_proc(t_command **av, int *flag, t_shell *proc);
char	*get_next_line(int fd);
int	red_output(t_redir *redir, t_shell *proc);
int	red_infile(t_redir *redir, t_shell *proc);
int	red_append_mode(t_redir *redir, t_shell *proc);

/*PROCESSES*/
void	first_process_util(t_shell *proc, t_command **av, char **envp);
void	last_process_util(t_shell *proc, t_command **av, char **envp);
void	middl_process(t_shell *proc, t_command **av, char **envp, int counter);
int	last_process(t_shell *proc, t_command **av, char **envp);
int	first_process(t_shell *proc, t_command **av, char **envp);
int	pipex_one_cmd(t_command **av, t_shell *proc, char **envp);

/*FREE FUNCTIONS*/
void	free_func_one_cmd(t_command **av, t_shell *proc);
void	terminate(char *display, t_shell *bash);
void	close_pipes(t_shell *proc);
void	free_env_list(t_list **head);

/*BONUS*/
void create_compound_array(t_shell *bash, t_token *headtoken);
void    execute(t_shell *bash);
int process_parens(t_compound **nodes, int start, t_shell *bash);


#endif
