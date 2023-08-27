/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:29:12 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/27 17:26:28 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
}					token_type;

typedef enum
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC,
}					t_redir_type;

typedef struct s_token
{
	token_type		type;
	char			*value;
	struct s_token	*next;
}					t_token;

/*Simple Command and Redirections Struct*/

typedef struct s_redir
{
	t_redir_type	type;
	char			*filename;
	struct s_redir	*next;
}					t_redir;

typedef struct s_command
{
	char			*cmd;
	int				cmd_len;
	int				args_len;
	char			**args;
	int				total_redirs;
	t_redir			*redirs;
}					t_command;

typedef struct s_shell
{
	t_command		*s_commands;
	char			**env_vars;
	t_list			*env_list;
	int				total_scommands;
	int				error_no;
	char			pwd[1024];
	int				fd[256][2];
	int				pid1;
	int				pid2;
	int				total_pipes;
	int				middle_scommand;
	int				scommand_index;
	int				counter;
	int process_id; // id1
	int				process_id1;
	char			*line;
	t_token			*tokenlist;
	t_list			temp_list;
	int				flag;
	int				flag_out;
	int				flag_in;
	int				check;
	int				x;
	int				dont;

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

int					error_status;

#ifndef PARSE_H
# define PARSE_H

/*PARSING*/
/*Array Methods*/
void				free_array(char **array);
int					ft_array_len(char **str);
bool				array_strchr(char *s, char c);
char				**dup_array(char **array);
bool				check_line(char *str);
char				**append_array(char **s1, char **s2);

/*Quote Methods*/
bool				check_unmatched_quotes(char *str);
void				set_quote_flag(t_quote *value, char c);

/*Words and Operators*/
char				**ft_space(char *s);
char				**ft_strtok(char *s);
char				**ft_split_on_delims(char *str);
t_token				*ft_tokenise(t_shell *bash, char **tokens);
t_token				*create_token_list(char **tokens);
void				free_token_list(t_token *tokenlist);

/*Syntax Check and Expansion*/
bool				token_syntax_check(t_token *headToken);
char				*final_expanded_str(t_shell *bash, char *str);
bool				needs_expansion(char *str);
int					get_search_var_end(char *str, int start);
int					get_end_index_expan(char *str, int start);
char				*strjoin_new_var(char *temp_str, char *expanded_str,
						int count);
char				**expand_array(t_shell *bash, char **str);

/*Simple Commands and Redirections*/
t_command			create_scmnd_node(t_token *start, t_token *end);
t_command			*create_scmnd_array(t_token **tokenlist);
void				fill_scmnd(t_command *scommand, t_token *start,
						t_token *end);
void				fill_redirs(t_command *scommand, t_token *redir,
						t_token *filename);
void				free_redirs_list(t_redir *redirlist);

/*Debugging*/
void				print_array(char **str);

/*EXECUTION*/

#endif
