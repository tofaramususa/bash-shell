/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:55:49 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/27 17:09:16 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

// Instead, each output redirection specifies a new output file, and the output is not overridden by subsequent redirections.
//fill redirection str struct with redirection and file name;
// with this function we fill the redirection struct of the simple command

static t_redir *get_to_last(t_redir *lst)
{
	t_redir	*to_last;

	to_last = lst;
	while (to_last != NULL && to_last->next != NULL)
		to_last = to_last->next;
	return (to_last);
}

static void add_to_redir_list(t_redir **redirList, t_redir *redirNode)
{
	t_redir *to_last;

	if (*redirList == NULL)
	{
		*redirList = redirNode;
	}
	else
	{
		to_last = get_to_last(*redirList);
		to_last->next = redirNode;
	}
}

static t_redir_type	assign_redir_type(char *arg)
{
    t_redir_type type;

    if (ft_strcmp(arg, "<") == 0)
        type = INPUT;
    else if (ft_strcmp(arg, ">") == 0)
        type = OUTPUT;
    else if (ft_strcmp(arg, ">>") == 0)
        type = APPEND;
    else
        type = HEREDOC;
    return (type);
}

void  fill_redirs(t_command *scommand, t_token *redir, t_token *filename)
{
    //create the t_direction node;
    t_redir *new_redir;

    new_redir = (t_redir *) malloc(sizeof(t_redir));
    // if(!new_redir_node)
        //do something
    new_redir->type = assign_redir_type(redir->value);
    new_redir->filename = ft_strdup(filename->value);
    new_redir->isfreed = false;
    new_redir->next = NULL;
    // printf("")
    if(new_redir->type == INPUT || new_redir->type == HEREDOC)
        add_to_redir_list(&scommand->redirs, new_redir);
    if(new_redir->type == OUTPUT || new_redir->type == APPEND)
        add_to_redir_list(&scommand->redirs, new_redir);
 
    //then check the type and if its outfile then check if have an outfile list already if not
    //malloc for it and add to the node
    //same for infile;  
}