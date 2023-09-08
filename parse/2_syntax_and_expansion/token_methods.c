/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_methods.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:48:25 by tmususa           #+#    #+#             */
/*   Updated: 2023/09/08 14:49:48 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static t_token	*get_to_last(t_token *lst)
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

static t_token_type	assign_t_token_type(char *arg)
{
	t_token_type	type;

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
	else if (ft_strcmp(arg, "&&") == 0)
		type = AND;
	else if (ft_strcmp(arg, "||") == 0)
		type = OR;
	else if (ft_strcmp(arg, "(") == 0)
		type = OPEN_PAREN;
	else if (ft_strcmp(arg, ")") == 0)
		type = CLOSE_PAREN;
	else
		type = WORD;
	return (type);
}

t_token	*new_token_node(char *arg)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (node)
	{
		node->value = ft_strdup(arg);
		node->type = assign_t_token_type(arg);
		node->isfreed = false;
		node->next = NULL;
	}
	return (node);
}

t_token	*create_token_list(char **tokens, t_shell *bash)
{
	t_token	*tokenlist;
	int		i;

	tokenlist = NULL;
	i = -1;
	bash->is_heredoc = false;
	while (tokens[++i])
	{
		if (needs_expansion(tokens[i]) == true && bash->is_heredoc == false)
		{
			expand_token(&tokenlist, tokens[i], bash);
			continue ;
		}
		bash->is_heredoc = false;
		if (tokens[i] && array_strchr(tokens[i], '*'))
		{
			if (filename_expansion(&tokenlist, tokens[i]))
				continue ;
		}
		if (tokens[i] && ft_strcmp("", tokens[i]) != 0)
			add_token_node(&tokenlist, new_token_node(tokens[i]));
		if (ft_strcmp("<<", tokens[i]) == 0)
			bash->is_heredoc = true;
	}
	return (tokenlist);
}
