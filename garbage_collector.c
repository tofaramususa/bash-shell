/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:33:48 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/30 19:31:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// function to free string:

void safe_free(void  *ptr) 
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

// function to free t_list list which is in libft envrionement variables and free_array env
void	free_env_list(t_list **head)
{
	t_list	*next;
	t_list *current;
	
	current = *head;
	// write_to_funcfile("free_env_list");
	if (current)
	{
		while (current)
		{
			next = current->next;
			if(current && current->isfreed == false)
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
// function to free redirections list which means calling filename/ safe_free
void	free_redirs_list(t_redir **redirlist)
{
	t_redir	*next_node;
	t_redir *current;
	// write_to_funcfile("free_redirs_list");
	current = *redirlist;
	if(current)
	{
		while(current)
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
// function to free_simple commands which simple commands
// safe_free command and path, free_array for args, call free redirs
static void	free_scommand(t_command ***s_commands)
{
	int	i;

	i = 0;
	// write_to_funcfile("free_scommand_called");
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

// function to free the shell which calls environment array and environment linked list,
	// function to free s_commands,

// function to free

// memory recovery function;

void garbage_collector(t_shell **bash)
{
    // write_to_funcfile("Garbage_collector_called");
    if (bash && *bash)
    {
		if ((*bash)->isfreed == false)
		{
			(*bash)->isfreed = true;
			if((*bash)->env_vars)
            	free_t_char(&((*bash)->env_vars));
			if((*bash)->s_commands)
            	free_scommand(&((*bash)->s_commands));
			if((*bash)->line)
            	safe_free((*bash)->line);
			if((*bash)->tokenlist)
            	free_token_list(&((*bash)->tokenlist));
        }
    }
}