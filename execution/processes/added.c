/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   added.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 07:03:17 by yonamog2          #+#    #+#             */
/*   Updated: 2023/09/06 20:29:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/**
 * exit_with_code: a function that exit with the status
 */
void	exit_with_code(t_command **av, t_shell *proc)
{
	if (av[proc->scommand_index]->cmd[ft_strlen(av[proc->scommand_index]->cmd)
		- 1] == '/')
	{
		ft_putstr_fd(": Is a directory\n", 2);
		garbage_collector(&proc);
		exit(126);
	}
	if (access(av[proc->scommand_index]->cmd, F_OK) == -1)
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		garbage_collector(&proc);
		exit(127);
	}
	else if (access(av[proc->scommand_index]->cmd, X_OK) == -1)
	{
		ft_putstr_fd(": Permission denied\n", 2);
		garbage_collector(&proc);
		exit(126);
	}
	else
	{
		ft_putstr_fd(": Is a directory\n", 2);
		garbage_collector(&proc);
		exit(126);
	}
}

/**
 * free_func_one_cmd: a function that free 2d array
 * @args: 2d array to be freed
 */
void	free_func_one_cmd(t_command **av, t_shell *proc)
{
	if (av[proc->scommand_index]->cmd
		&& av[proc->scommand_index]->cmd[0] != '\0')
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(av[proc->scommand_index]->cmd, 2);
		exit_with_code(av, proc);
	}
	garbage_collector(&proc);
	exit(0);
}

/**
 * terminate: a function that print error
 *	@m: the string to dispplay before
 */

void	terminate(char *display, t_shell *bash)
{
	if (access(display, W_OK) == -1 || access(display, R_OK) == -1)
		perror(display);
	else
		perror(display);
	close_pipes(bash);
	garbage_collector(&bash);
	exit(1);
}

/**

	* cmd_not_found: a function that prints command not found and exit with 127 code
 * @res: a 2d array which contains the string name to be printed
 */
void	cmd_not_found(t_command **av, t_shell *proc, int counter)
{
	ft_putstr_fd("bash: ", 2);
	write(2, av[counter]->cmd, ft_strlen(av[counter]->cmd));
	ft_putstr_fd(": command not found\n", 2);
	garbage_collector(&proc);
	exit(127);
}
