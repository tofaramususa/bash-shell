/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_methods.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:57:48 by tmususa           #+#    #+#             */
/*   Updated: 2023/09/08 17:58:56 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	free_short(char *path, char **path_split)
{
	safe_free(path);
	free_array(path_split);
}

void	collect_and_exit(t_shell *bash, char *message)
{
	garbage_collector(&bash);
	exit(printf("%s\n", message));
}

void	free_token_list(t_token **tokenlist)
{
	t_token	*next_node;
	t_token	*current;

	current = *tokenlist;
	if (current)
	{
		while (current)
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
