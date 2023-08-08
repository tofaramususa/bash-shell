/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:55:40 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/05 21:47:35 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "3. Tokens/tokens.h"

typedef enum {
    INPUT,      // '<' redirection
    OUTPUT,     // '>' redirection
    APPEND,     // '>>' redirection
    HEREDOC,             // Here-document redirection
} t_redirection_type;

typedef struct t_redirection {
    t_redirection_type type;
    int fd;      // For file-descriptor redirections
    char *heredoc_data;  // For here-document redirection
    struct t_redirection  *next; //next redirection
} t_redirection;

typedef struct t_commandNode {
    char **args;
    char *path;
    t_redirection *outfile;
    t_redirection *infile;
    struct t_commandNode *prev;
    struct t_commandNode *next;
} t_commandNode;

typedef struct t_shell
{
    t_commandNode **simple_commands;
    int *envp;
	
} t_shell;


