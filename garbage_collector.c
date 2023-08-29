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

void safe_free(void *ptr) 
{
    if (ptr)
		free(ptr);
    ptr = NULL;
}

// function to free t_list list which is in libft envrionement variables and free_array env
void	free_env_list(t_list *head)
{
	t_list	*current;
	t_list	*next;

	if (head)
	{
		current = head;
		while (current != NULL && current->isfreed == false)
		{
			next = current->next;
			safe_free(current->key);
			safe_free(current->value);
			safe_free(current);
			current->isfreed = true;
			current = next;
		}
		head = NULL;
	}
}
// function to free redirections list which means calling filename/ safe_free
void	free_redirs_list(t_redir *redirlist)
{
	t_redir	*next_node;

	if (redirlist)
	{
		while (redirlist && redirlist->isfreed == false)
		{
			next_node = redirlist->next;
			safe_free(redirlist->filename);
			safe_free(redirlist);
			redirlist->isfreed = true;
			redirlist = next_node;
		}
		redirlist = NULL;
	}
}
// function to free_simple commands which simple commands
// safe_free command and path, free_array for args, call free redirs
void	free_scommand(t_command **s_commands)
{
	int	i;

	i = 0;
	write_to_funcfile("free_scommand_called");
	if (s_commands)
	{
		while (s_commands[i] != NULL && s_commands[i]->isfreed == false)
		{
			safe_free(s_commands[i]->cmd);
			free_array(s_commands[i]->args);
			free_redirs_list(s_commands[i]->redirs);
			s_commands[i]->isfreed = true;
			i++;
		}
		s_commands = NULL;
	}
}

// function to free the shell which calls environment array and environment linked list,
	// function to free s_commands,

// function to free

// memory recovery function;

void	garbage_collector(t_shell *bash)
{
	write_to_funcfile("Garbage_collector_called");
	if (bash && bash->isfreed == false)
	{
		// call function to free env_vars;
		// free_array(bash->env_vars);
		// // call function to free s_commands;
		// free_scommand(bash->s_commands);
		// safe_free(bash->line);
		// // call function to free token;
		// free_token_list(bash->tokenlist);
		// free_env_list(bash->temp_list);
		bash->isfreed = true; 
	}
}