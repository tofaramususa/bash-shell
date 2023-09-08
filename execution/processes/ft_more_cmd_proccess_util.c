/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_more_cmd_proccess_util.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:18:07 by yonamog2          #+#    #+#             */
/*   Updated: 2023/09/08 14:29:10 by tmususa          ###   ########.fr       */
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

void	init_parsing(t_shell *proc)
{
	proc->x = -1;
	proc->temp_list = proc->env_list;
	proc->path = NULL;
	proc->result = NULL;
}

/**
 * set_signal_exe: set the singal and execute for one cmd
 * @proc: struct that have all the variables i use
 * @av: structure of the commands
 * @envp: 2d array conataining the environment variables
 */
int	set_signal_exe(t_command **av, t_shell *proc, char **envp)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, child_sig_handler);
	signal(SIGQUIT, child_sig_handler);
	one_cmd_process(proc, av, envp);
	waitpid(-1, &proc->error_no, 0);
	if (WIFEXITED(proc->error_no))
		return (WEXITSTATUS(proc->error_no));
	else if (WIFSIGNALED(proc->error_no))
		return (WTERMSIG(proc->error_no) + 128);
	return (0);
}

int	search(char **envp)
{
	int	x;

	x = -1;
	while (envp[++x])
		if (ft_strnstr(envp[x], "PATH=", 5))
			return (1);
	return (0);
}
