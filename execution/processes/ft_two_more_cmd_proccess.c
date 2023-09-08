/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_two_more_cmd_proccess.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 13:07:19 by yonamog2          #+#    #+#             */
/*   Updated: 2023/09/08 15:21:59 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/**
 * check_built_ins_and_exexute: check if the command is one of the built ins
 * and execute
 * @proc: struct that have all the variables i use
 * @av: structure of the commands
 * @envp: 2d array conataining the environment vasriables
 */
void	check_built_ins_and_exexute(t_shell *proc, t_command **av, char **envp)
{
	int	ret;

	ret = 0;
	(void)envp;
	if (proc->check == 1)
		ft_exit(av, proc);
	else if (proc->check == 2)
		ft_echo(av, proc);
	else if (proc->check == 3)
		ret = ft_cd(av, proc);
	else if (proc->check == 4)
		ft_pwd(proc);
	else if (proc->check == 5)
		ft_env_print_linked(proc);
	else if (proc->check == 6)
		ret = ft_export_print_linked(av, proc);
	else if (proc->check == 7)
		ret = ft_unset(av, proc);
	exit(ret);
}

/**
 * first_process: executing the first command
 * @proc: struct that have all the variables i use
 * @av: structure of the commands
 * @envp: 2d array conataining the environment variables
 */
int	first_process(t_shell *proc, t_command **av, char **envp)
{
	proc->index = 0;
	proc->flag = 0;
	proc->process_id = fork();
	if (proc->process_id < 0)
		terminate("fork", proc);
	if (proc->process_id == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (av[0]->total_redirs > 0)
			red_first_proc(&av[0], &proc->flag, proc);
		if (proc->flag == 0)
			dup2(proc->fd[0][1], STDOUT_FILENO);
		close_pipes(proc);
		if (av[0]->cmd == NULL)
		{
			garbage_collector(&proc);
			exit(0);
		}
		proc->check = ft_check_builtin(av[0]->cmd);
		first_process_util(proc, av, envp);
	}
	return (proc->process_id);
}

/**
 * middle_proc_execute: execution of the middle command util
 * @proc: struct that have all the variables i use
 * @av: structure of the commands
 * @envp: 2d array conataining the environment variables
 */
void	middle_proc_execute(t_shell *proc, t_command **av, char **envp,
		int counter)
{
	char	*tmp;

	tmp = get_command(proc, envp, av[counter]->cmd);
	if (av[counter]->cmd && tmp && av[counter]->cmd[0])
	{
		proc->index = counter;
		execve(tmp, av[counter]->args->array, envp);
		safe_free(tmp);
		free_func_one_cmd(av, proc);
	}
	else
		cmd_not_found(av, proc, counter);
}

/**
 * middl_process: execution of the middle command
 * @proc: struct that have all the variables i use
 * @av: structure of the commands
 * @envp: 2d array conataining the environment variables
 */
void	middl_process(t_shell *proc, t_command **av, char **envp, int counter)
{
	proc->index = counter;
	proc->flag_out = 0;
	proc->flag_in = 0;
	proc->process_id = fork();
	if (proc->process_id < 0)
		terminate("fork", proc);
	if (proc->process_id == 0)
	{
		if (av[counter]->total_redirs > 0)
			red_middle(av, &proc->flag_out, &proc->flag_in, proc);
		if (proc->flag_out == 0)
			dup2(proc->fd[proc->counter + 1][1], STDOUT_FILENO);
		if (proc->flag_in == 0)
			dup2(proc->fd[proc->counter][0], STDIN_FILENO);
		close_pipes(proc);
		if (av[counter]->cmd == NULL)
		{
			garbage_collector(&proc);
			exit(0);
		}
		proc->check = ft_check_builtin(av[counter]->cmd);
		if (proc->check > 0)
			check_built_ins_and_exexute(proc, av, envp);
		middle_proc_execute(proc, av, envp, counter);
	}
}

/**
 * last_process: execution of last command
 * @proc: struct that have all the variables i use
 * @av: structure of the commands
 * @envp: 2d array conataining the environment variables
 */
int	last_process(t_shell *proc, t_command **av, char **envp)
{
	proc->index = (*av)->cmd_len - 1;
	proc->flag = 0;
	proc->process_id1 = fork();
	if (proc->process_id1 < 0)
		terminate("fork", proc);
	if (proc->process_id1 == 0)
	{
		if (av[(*av)->cmd_len - 1]->total_redirs > 0)
			red_last_proc(av, &proc->flag, proc);
		if (proc->flag == 0)
			dup2(proc->fd[proc->counter][0], STDIN_FILENO);
		close_pipes(proc);
		if (av[(*av)->cmd_len - 1]->cmd == NULL)
		{
			garbage_collector(&proc);
			exit(0);
		}
		proc->check = ft_check_builtin(av[(*av)->cmd_len - 1]->cmd);
		if (proc->check > 0)
			check_built_ins_and_exexute(proc, av, envp);
		last_process_util(proc, av, envp);
	}
	return (proc->process_id1);
}
