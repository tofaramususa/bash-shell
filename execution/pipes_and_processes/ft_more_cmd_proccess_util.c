/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_more_cmd_proccess_util.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:18:07 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/15 17:34:06 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/**
 * first_process_util: 
*/
void	first_process_util(t_shell *proc, t_command *av, char **envp) //for the first command, check for command perform execve
{
	char	*tmp;

	if (av[0].cmd && proc->check > 0)
		check_built_ins_and_exexute(proc, av, envp);
	tmp = get_command(proc, envp, av[0].cmd); //function to search for command name
	if (av[0].cmd && tmp && av[0].cmd[0]) //check if there is command and its not a NULL terminator then execute
	{
		execve(tmp, av[0].args, envp);
		free_func_one_cmd(av, proc, envp);
	}
	else
		cmd_not_found(av, proc, 0); //same here check if there's something if not then free
}

void	last_process_util(t_shell *proc, t_command *av, char **envp) //call the execve function
{
	char	*tmp;

	tmp = get_command(proc, envp, av[av->cmd_len - 1].cmd); //check for command name
	if (av[av->cmd_len - 1].cmd && tmp && av[av->cmd_len - 1].cmd[0])
	{
		execve(tmp, av[av->cmd_len - 1].args, envp);
		free_func_one_cmd(av, proc, envp);
	}
	else
		cmd_not_found(av, proc, av->cmd_len - 1); //here is the command not found function which means we need to free, put it at the end
}
