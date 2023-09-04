/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compound_methods.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 20:20:34 by tmususa           #+#    #+#             */
/*   Updated: 2023/09/03 21:12:16 by marvin           ###   ########.fr       */
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

void	create_compound_array(t_shell *bash, t_token *headtoken)
{
	t_token *temp;
	t_token *end;
	token_type split_on;
	t_paren_type paren;
	int i;

	temp = headtoken;
	bash->cmpd_node = (t_compound **)malloc(sizeof(t_compound *)
		* (count_compound(headtoken) + 1));
	i = -1;
	split_on = PIPE;
	while (++i < count_compound(headtoken))
	{
		paren = NOT_PAREN;
		while (temp && temp->type == OPEN_PAREN)
		{
			temp = temp->next;
			paren = AFTER_OPEN_PAREN;
		}
		end = temp;
		while (end->next != NULL && end->next->type != OR
			&& end->next->type != AND)
		{
			if (end->next->type == CLOSE_PAREN)
				paren = BEFORE_CLOSE_PAREN;
			end = end->next;
		}
		bash->cmpd_node[i] = create_compound_node(temp, end, bash);
		bash->cmpd_node[i]->split_on = split_on;
		if (end && end->next && end->next->type == OR)
			split_on = OR;
		if (end && end->next && end->next->type == AND)
			split_on = AND;
		if (end && end->next != NULL)
			end = end->next->next;
		bash->cmpd_node[i]->paren = paren;
		bash->cmpd_node[i]->isfreed = false;
		temp = end;
	}
	
	bash->cmpd_node[i] = NULL;
}