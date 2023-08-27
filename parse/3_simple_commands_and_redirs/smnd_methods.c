/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smnd_methods.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:56:11 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/27 17:09:16 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"


static int count_redirs(t_redir *redirs)
{
	t_redir *temp;
	int total;

	total = 0;
	temp = redirs
	while (temp)
		total++ ;
	return (total);
}
// in our tokens list we know the start and stop of our simple command now we parse it to the tokens into our simple commands
t_command	*create_scmnd_node(t_token *start, t_token *end)
{
	t_command	*command;

	command = malloc(sizeof(t_command *));
	if (!command)
		return (NULL);
	command->cmd = NULL;
	command->redirs = NULL;
	command->args = NULL;
	fill_scmnd(&command, start, end);
	if (command->args[0])
		command->cmd = command->args[0];
	command->args_len = ft_array_len(command->args);
	command->total_redirs = count_redirs(command->redirs);

	return (command);
}

static void	add_token_to_args(t_command *scommand, t_token *current_token)
{
	char	**temp_array;

	if (scommand->args == NULL) // create our initial array with the first word
	{
		scommand->args = (char **)malloc(sizeof(char *) * 2);
			// create malloc function;;
		scommand->args[0] = ft_strdup(current_token->value);
		scommand->args[1] = NULL;
	}
	else
	{
		temp_array = (char **)malloc(sizeof(char *) * 2);
		temp_array[0] = ft_strdup(current_token->value);
		temp_array[1] = NULL;
		;
		scommand->args = append_array(scommand->args, temp_array);
			// l need to understand something here,
			where is the copy of ft_strdup store and how do l free it
		free_array(temp_array);
	}
}

// else we add to args array,
	then we take the first arg and make a copy of that for char *command;
void	fill_scmnd(t_command *scommand, t_token *start, t_token *end)
{
	t_token	*current_token;

	current_token = start;
	while (current_token && current_token != end->next)
	{
		if (current_token->type == REDIR)
		{
			fill_redirs(scommand, current_token, current_token->next);
				// fill redirection str struct with redirection and file name;
			current_token = current_token->next->next;                
				// skip the next two;
		}
		// add array to while not at the end no redirection found;
		while (current_token && (current_token != end->next
				&& current_token->type != REDIR))
		{
			add_token_to_args(scommand, current_token);
			current_token = current_token->next;
		}
	}
	if (scommand->args)
		scommand->cmd = scommand->args[0];
}