/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:33:48 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/27 17:23:04 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// function to free string:
void	safefree(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

// function to free t_list list which is in libft envrionement variables and free_array env
void	free_env_list(t_list *head)
{
	t_list	*current;
	t_list	*next;

	if (head)
	{
		current = head;
		while (current != NULL)
		{
			next = current->next;
			safefree(current->key);
			safefree(current->value);
			safefree(current);
			current = next;
		}
	}
	head = NULL;
}
// function to free redirections list which means calling filename/ safefree
void	free_redirs_list(t_redir *redirlist)
{
	t_redir	*current_node;
	t_redir	*next_node;

	if (redirlist)
	{
		current_node = redirlist;
		while (current_node)
		{
			next_node = current_node->next;
			safefree(current_node->filename);
			safefree(current_node);
			current_node = next_node;
		}
	}
	redirlist = NULL;
}
// function to free_simple commands which simple commands
// safefree command and path, free_array for args, call free redirs
void	free_scommand(t_command **s_commands)
{
	int	i;

	i = 0;
	if (s_commands)
	{
		while (s_commands[i] != NULL)
		{
			safefree(s_commands[i]->cmd);
			free_array(s_commands[i]->args);
			free_redirs_list(s_commands[i]->redirs);
			i++;
		}
	}
	s_commands = NULL;
}

// function to free the shell which calls environment array and environment linked list,
	// function to free s_commands,

// function to free

// memory recovery function;

void	garbage_collector(t_shell *bash)
{
	if (bash)
	{
		// call function to free env_vars;
		free_array(bash->env_vars);
		// call function to free s_commands;
		free_scommand(bash->s_commands);
		// call function to free env_list;
		free_env_list(bash->env_list);
		// call function to free line;
		safefree(bash->line);
		// call function to free token;
		free_token_list(bash->tokenlist);
	}
}