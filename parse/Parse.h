/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:27:52 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/16 19:33:11 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <string.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
#include <stdint.h>
# include  "Libft/libft.h"

/*Quotes Struct*/
typedef struct s_quote
{
    bool single_q;
    bool double_q;
} t_quote;

/*Tokens Struct*/
typedef enum 
{
    WORD,
    REDIR,
    PIPE,
}   token_type;

typedef struct s_token
{
    token_type type;
    char *value;
    struct t_token *next;
} t_token;

/*Simple Command and Redirections Struct*/
typedef enum {
    INPUT,
    OUTPUT,
    APPEND,
    HEREDOC,
} t_redir_type;

typedef struct s_redir {
    t_redir_type type;
    char *filename;
    char *heredoc_data;
    struct t_redir *next;
} t_redir;

typedef struct s_command 
{
	char *command;
    char *path;
    char **args;
    t_redir *redir;
} t_command;

#ifndef PARSE_H
# define PARSE_H

/*Array Methods*/
void free_array(char **array);
int ft_array_len(char **str);
bool	array_strchr(char *s, char c);
char **dup_array(char **array);
bool check_line(char *str);
char **append_array(char  **s1, char **s2);

/*Quote Methods*/
bool check_unmatched_quotes(char *str);
void set_quote_flag(t_quote *value, char c);

/*Words and Operators*/
char	**ft_space(char *s);
char	**ft_strtok(char *s);
char	**ft_split_on_delims(char *str);
t_token *ft_tokenise(t_shell *bash, char **tokens);
t_token *create_token_list(char **tokens);
void free_token_list(t_token **tokenlist);

/*Syntax Check and Expansion*/
bool token_syntax_check(t_token *headToken);
char	*final_expanded_str(t_shell *bash, char *str);
bool needs_expansion(char *str);
int get_search_var_end(char *str, int start);
int	get_end_index_expan(char *str, int start);
char *strjoin_new_var(char *temp_str, char *expanded_str, int count);
char **expand_array(t_shell *bash, char **str);

/*Simple Commands and Redirections*/
t_command create_scmnd_node(t_token *start, t_token *end);
t_command *create_scmnd_array(t_token **tokenlist);
void fill_scmnd(t_command *scommand, t_token *start, t_token *end);
void  fill_redirs(t_command *scommand, t_token *redir, t_token *filename);

/*Debugging*/
void print_array(char **str);

#endif