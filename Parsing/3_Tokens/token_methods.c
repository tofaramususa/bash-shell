/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_methods.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:48:25 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/05 21:40:04 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

//essentially main function to turn every word and operator to a token
t_token **create_token_list(char **tokens)
{
    t_token	**tokenList;
	int	i;


    tokenList = malloc(sizeof(t_token *));
    if (!tokenList)
	{
		free_array(tokens);
		return (NULL);
	}
	i = -1;
	tokenList = NULL;
	while (tokens[++i])
		add_token_node(tokenList, new_token_node(tokens[i]));
    return(tokenList);
}

//lstaddtoback with differrent name
void	add_token_node(t_token **tokenList, t_token *tokenNode)
{
	t_token	*to_last;

	if (*tokenList)
	{
		to_last = ft_lstlast(*tokenList);
		to_last->next = tokenNode;
		tokenNode->next = NULL;
	}
	else
		*tokenList = tokenNode;
}

//need to create ft_strcmp, this is untested 
token_type	*assign_token_type(char *arg)
{
    token_type *type;

    type = (token_type *) malloc(sizeof(token_type));

    if (!type)
        return (NULL);
    // else if (ft_strcmp(arg, "\n") == 0)
    //     *type = NEWLINE
    else if (ft_strcmp(arg, "<") == 0)
        *type = REDIR;
    else if (ft_strcmp(arg, ">") == 0)
        *type = REDIR;
    else if (ft_strcmp(arg, ">>") == 0)
        *type = REDIR;
    else if (ft_strcmp(arg, "<<") == 0)
        *type = REDIR;
    else if (ft_strcmp(arg, "|") == 0)
        *type = PIPE;
    else
        *type = WORD;
    return (type);
}

//lstnew
t_token	*new_token_node(char *arg)
{
	t_token	*node;

	node = (t_token *) malloc(sizeof(t_token));
	if (!node)
		return (0);
	node->value = arg;
	node->type = assign_token_type(arg);
	node->next = NULL;
	return (node);
}

//free everything
void    free_token_list(t_token **tokenList)
{
    t_token *current_node;
    t_token *next_node;

    current_node = tokenList;

    while (current_node != NULL)
    {
        // Store the next node before freeing the current node
        next_node = current_node->next;
        // Free the value string (if it's not NULL)
        if (current_node->value != NULL)
            free(current_node->value);
        free(current_node);
        current_node = next_node;
    }
    *tokenList = NULL;
}
