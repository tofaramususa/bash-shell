/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_methods.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:48:25 by tmususa           #+#    #+#             */
/*   Updated: 2023/09/05 13:45:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static t_token *get_to_last(t_token *lst)
{
	t_token	*to_last;

	to_last = lst;
	while (to_last != NULL && to_last->next != NULL)
		to_last = to_last->next;
	return (to_last);
}

void	add_token_node(t_token **tokenlist, t_token *tokenNode)
{
	t_token	*to_last;
	//need to handle when either are NULL, not only the tokenlist
	if (*tokenlist)
	{
		to_last = get_to_last(*tokenlist);
		to_last->next = tokenNode;
		tokenNode->next = NULL;
	}
	else
	{
		*tokenlist = tokenNode;
	}
}
 
static token_type	assign_token_type(char *arg)
{
    token_type type;

    if (ft_strcmp(arg, "<") == 0)
        type = REDIR;
    else if (ft_strcmp(arg, ">") == 0)
        type = REDIR;
    else if (ft_strcmp(arg, ">>") == 0)
        type = REDIR;
    else if (ft_strcmp(arg, "<<") == 0)
        type = REDIR;
    else if (ft_strcmp(arg, "|") == 0)
        type = PIPE;
    else if(ft_strcmp(arg, "&&") == 0)
		type = AND;
    else if(ft_strcmp(arg, "||") == 0)
		type = OR;
    else if(ft_strcmp(arg, "(") == 0)
		type = OPEN_PAREN;
    else if(ft_strcmp(arg, ")") == 0)
		type = CLOSE_PAREN;
    else
		type = WORD;
    return (type);
}

t_token	*new_token_node(char *arg)
{
	t_token	*node;

	node = (t_token *) malloc(sizeof(t_token));
	if (node)
	{
		node->value = ft_strdup(arg);
		node->type = assign_token_type(arg);
		node->isfreed = false;
		node->next = NULL;
	}
	return (node);
}

//free everything
void free_token_list(t_token **tokenlist)
{
    t_token *next_node;
	t_token	*current;
	
	current = *tokenlist;
	// write_to_funcfile("Garbage_collector_called");
	if(current)
	{
		while(current)
		{
			next_node = current->next;
			if (current && current->isfreed == false)
			{
				current->isfreed = true;
				free(current->value);
				free(current);
			}
			current = next_node;
		}
		*tokenlist = NULL;
	}
}

//essentially main function to turn every word and operator to a token
t_token *create_token_list(char **tokens, t_shell *bash)
{
    t_token	*tokenlist; //pointer to the head
	int	i;
	bool heredoc;

	tokenlist = NULL;
	i = -1;
	heredoc = false;
	while (tokens[++i])
	{
		if(needs_expansion(tokens[i]) == true && heredoc == false)
		{
			expand_token(&tokenlist, tokens[i], bash);
			continue;
		}
		heredoc = false;
		if(tokens[i] && array_strchr(tokens[i], '*'))
		{
			if (filename_expansion(&tokenlist, tokens[i]))
				continue ;	
		}
		if(tokens[i] && ft_strcmp("",tokens[i]) == 0)
			continue;
		add_token_node(&tokenlist, new_token_node(tokens[i])); //this is essentially add to back and we are creating a node from every token we have
		if(ft_strcmp("<<", tokens[i]) == 0)
			heredoc = true;
	}
    return(tokenlist);
}