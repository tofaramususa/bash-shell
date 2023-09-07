/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:09:42 by yonamog2          #+#    #+#             */
/*   Updated: 2023/01/23 19:27:14 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/**
 * first proc redirection
 * @av: the structure that contain the specific pipe
 * @flag: the output redirection flag
 */
void	red_first_proc(t_command **av, int *flag, t_shell *proc)
{
	t_redir	*temp;

	temp = av[0]->redirs;
	while (temp)
	{
		if (temp->type == OUTPUT)
			*flag = red_output(temp, proc);
		else if (temp->type == INPUT)
			red_infile(temp, proc);
		else if (temp->type == APPEND)
			*flag = red_append_mode(temp, proc);
		temp = temp->next;
	}
}

/**
 * red_one_cmd-> redirection for middle command
 * @av: the structure that contain the specific pipe
 */
void	red_one_cmd(t_command **av, t_shell *proc)
{
	t_redir	*temp;

	temp = av[proc->scommand_index]->redirs;
	while (temp)
	{
		if (temp->type == OUTPUT)
			red_output(temp, proc);
		else if (temp->type == INPUT)
			red_infile(temp, proc);
		else if (temp->type == APPEND)
			red_append_mode(temp, proc);
		temp = temp->next;
	}
}
/**
 * red_middle-> redirection for middle command
 * @av: the structure that contain the specific pipe
 * @flag_out: the flag to check output redirection
 * @flag_in: the flag to check input redirection
 */

void	red_middle(t_command **av, int *flag_out, int *flag_in, t_shell *proc)
{
	t_redir	*temp;

	temp = av[proc->scommand_index]->redirs;
	while (temp)
	{
		if (temp->type == OUTPUT)
			*flag_out = red_output(temp, proc);
		else if (temp->type == INPUT)
			*flag_in = red_infile(temp, proc);
		else if (temp->type == APPEND)
			*flag_out = red_append_mode(temp, proc);
		temp = temp->next;
	}
}

/**
 * redirection for the last command
 * @av: the structure that contain the specific pipe
 * @flag: the flag to check if we redirect to a file or not
 * or itll stay in the default
 */
void	red_last_proc(t_command **av, int *flag, t_shell *proc)
{
	t_redir	*temp;

	temp = av[proc->scommand_index]->redirs;
	while (temp)
	{
		proc->scommand_index = (*av)->cmd_len - 1;
		if (temp->type == OUTPUT)
			red_output(temp, proc);
		else if (temp->type == INPUT)
			*flag = red_infile(temp, proc);
		else if (temp->type == APPEND)
			red_append_mode(temp, proc);
		temp = temp->next;
	}
}
