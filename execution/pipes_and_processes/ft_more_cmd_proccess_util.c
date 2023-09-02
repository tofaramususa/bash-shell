/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_more_cmd_proccess_util.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:18:07 by yonamog2          #+#    #+#             */
/*   Updated: 2023/09/02 21:53:38 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/**
 * first_process_util:
 */
void	first_process_util(t_shell *proc, t_command **av, char **envp)
{
	char	*tmp;

	if (av[0]->cmd && proc->check > 0)
		check_built_ins_and_exexute(proc, av, envp);
	tmp = get_command(proc, envp, av[0]->cmd);
	if (av[0]->cmd && tmp && av[0]->cmd[0])
	{
		execve(tmp, av[0]->args->array, envp);
		free_func_one_cmd(av, proc);
	}
	else
		cmd_not_found(av, proc, 0);
}

void	last_process_util(t_shell *proc, t_command **av, char **envp)
{
	char	*tmp;

	tmp = get_command(proc, envp, av[(*av)->cmd_len - 1]->cmd);
	if (av[(*av)->cmd_len - 1]->cmd && tmp && av[(*av)->cmd_len - 1]->cmd[0])
	{
		execve(tmp, av[(*av)->cmd_len - 1]->args->array, envp);
		free_func_one_cmd(av, proc);
	}
	else
		cmd_not_found(av, proc, (*av)->cmd_len - 1);
}
