/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_methods.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 20:20:34 by tmususa           #+#    #+#             */
/*   Updated: 2023/09/08 17:50:27 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static int	count_compound(t_token *headtoken)
{
	int		i;
	t_token	*temp;

	temp = headtoken;
	i = 1;
	while (temp)
	{
		if (temp->type == AND || temp->type == OR)
			i++;
		temp = temp->next;
	}
	return (i);
}

t_token_type	fill_compound_node(t_shell *bash, t_token *temp, t_token *end)
{
	bash->cmpd_node[bash->i] = (t_compound *)malloc(sizeof(t_compound));
	if (!bash->cmpd_node[bash->i])
		collect_and_exit(bash, "memory allocation failure");
	create_compound_node(temp, end, bash, bash->cmpd_node[bash->i]);
	bash->cmpd_node[bash->i]->cmd_len = count_pipes(temp, end);
	bash->cmd_len = bash->cmpd_node[bash->i]->cmd_len;
	bash->cmpd_node[bash->i]->split_on = bash->split_on;
	bash->cmpd_node[bash->i]->paren = bash->paren;
	bash->cmpd_node[bash->i]->isfreed = false;
	if (end && end->next && end->next->type == OR)
		return (OR);
	if (end && end->next && end->next->type == AND)
		return (AND);
	return (PIPE);
}

void	check_paren_type(t_shell *bash, t_token *end)
{
	if (end->next->type == CLOSE_PAREN)
		bash->paren = BEFORE_CLOSE_PAREN;
}

void	go_past_open_paren(t_token **temp, t_shell *bash)
{
	while (*temp && (*temp)->type == OPEN_PAREN)
	{
		*temp = (*temp)->next;
		bash->paren = AFTER_OPEN_PAREN;
	}
}

void	create_compound_array(t_shell *bash, t_token *headtoken)
{
	t_token	*temp;
	t_token	*end;

	temp = headtoken;
	bash->cmpd_node = (t_compound **)malloc(sizeof(t_compound *)
			* (count_compound(headtoken) + 1));
	bash->i = -1;
	while (++bash->i < count_compound(headtoken))
	{
		bash->paren = NOT_PAREN;
		go_past_open_paren(&temp, bash);
		end = temp;
		while (end->next != NULL && end->next->type != OR
			&& end->next->type != AND)
		{
			check_paren_type(bash, end);
			end = end->next;
		}
		bash->split_on = fill_compound_node(bash, temp, end);
		if (end && end->next != NULL)
			end = end->next->next;
		temp = end;
	}
	bash->cmpd_node[bash->i] = NULL;
}
