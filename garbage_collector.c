/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:33:48 by tmususa           #+#    #+#             */
/*   Updated: 2023/09/02 21:03:36 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_list(t_list **head)
{
	t_list	*next;
	t_list	*current;

	current = *head;
	if (current)
	{
		while (current)
		{
			next = current->next;
			if (current && current->isfreed == false)
			{
				current->isfreed = true;
				free(current->key);
				free(current->value);
				free(current);
			}
			current = next;
		}
		*head = NULL;
	}
}

void	free_redirs_list(t_redir **redirlist)
{
	t_redir	*next_node;
	t_redir	*current;

	current = *redirlist;
	if (current)
	{
		while (current)
		{
			next_node = current->next;
			if (current && current->isfreed == false)
			{
				current->isfreed = true;
				free(current->filename);
				free(current);
			}
			current = next_node;
		}
		*redirlist = NULL;
	}
}

static void	free_scommand(t_command ***s_commands)
{
	int	i;

	i = 0;
	if (s_commands && *s_commands)
	{
		while ((*s_commands)[i])
		{
			if ((*s_commands)[i]->isfreed == false)
			{
				(*s_commands)[i]->isfreed = true;
				free((*s_commands)[i]->cmd);
				free_t_char(&(*s_commands)[i]->args);
				free_redirs_list(&(*s_commands)[i]->redirs);
				free((*s_commands)[i]);
			}
			i++;
		}
		free(*s_commands);
		*s_commands = NULL;
	}
}

void	free_compoundlist(t_compound ***nodes)
{
	int	i;

	i = 0;
	if (nodes && *nodes)
	{
		while ((*nodes)[i])
		{
			if ((*nodes)[i]->isfreed == false)
			{
				(*nodes)[i]->isfreed = true;
				if ((*nodes)[i]->s_commands)
					free_scommand(&((*nodes)[i]->s_commands));
				free((*nodes)[i]);
			}
			i++;
		}
	}
	free(*nodes);
	*nodes = NULL;
}

void	garbage_collector(t_shell **bash)
{
	if (bash && *bash)
	{
		if ((*bash)->isfreed == false)
		{
			(*bash)->isfreed = true;
			if ((*bash)->env_vars)
				free_t_char(&((*bash)->env_vars));
			if ((*bash)->line)
				safe_free((*bash)->line);
			if ((*bash)->cmpd_node)
				free_compoundlist(&((*bash)->cmpd_node));
			if ((*bash)->tokenlist)
				free_token_list(&((*bash)->tokenlist));
			if	((*bash)->env_list)
				free_env_list(&(*bash)->env_list);
		}
		free(*bash);
	}
}
