/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:21:08 by yonamog2          #+#    #+#             */
/*   Updated: 2023/09/08 17:59:12 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/**
 * ft_check_builtin: check if the command is one of the built-in
 * @cmd: the command to check
 */
int	ft_check_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (2);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (3);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (4);
	else if (ft_strcmp(cmd, "env") == 0)
		return (5);
	else if (ft_strcmp(cmd, "export") == 0)
		return (6);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (7);
	return (0);
}

/**
 * pipex_two_cmd: execute and return err_code for two cmd
 * @av: a structure that contains the whole variables
 * @proc: a struture which contains the command and redirection
 * @envp: the environment variable
 */
int	pipex_two_cmd(t_command **av, t_shell *proc, char **envp)
{
	signal(SIGINT, SIG_IGN);
	proc->pid1 = first_process(proc, av, envp);
	proc->pid2 = last_process(proc, av, envp);
	close_pipes(proc);
	waitpid(proc->pid2, &proc->error_no, 0);
	waitpid(proc->pid1, 0, 0);
	signal(SIGINT, sig_handler);
	if (WIFEXITED(proc->error_no))
		return (WEXITSTATUS(proc->error_no));
	else if (WIFSIGNALED(proc->error_no))
		return (WTERMSIG(proc->error_no) + 128);
	return (0);
}

/**
 * pipex_three_cmd: execute and return err_code for two cmd
 * @av: a structure that contains the whole variables
 * @proc: a struture which contains the command and redirection
 * @envp: the environment variable
 */
int	pipex_three_cmd(t_command **av, t_shell *proc, char **envp)
{
	proc->x = 0;
	proc->counter = 0;
	signal(SIGINT, SIG_IGN);
	first_process(proc, av, envp);
	while (proc->counter < proc->middle_scommand)
	{
		middl_process(proc, av, envp, proc->counter + 1);
		proc->counter++;
	}
	proc->pid2 = last_process(proc, av, envp);
	close_pipes(proc);
	proc->counter = -1;
	waitpid(proc->pid2, &proc->error_no, 0);
	while (proc->x < ((*av)->cmd_len - 1))
	{
		waitpid(-1, 0, 0);
		proc->x++;
	}
	if (WIFEXITED(proc->error_no))
		return (WEXITSTATUS(proc->error_no));
	else if (WIFSIGNALED(proc->error_no))
		return (WTERMSIG(proc->error_no) + 128);
	return (0);
}

/**
 * pipex: where the main execution is happening,
 * it will execute one two and three cmds
 * @av: a structure that contains the whole variables
 * @ac: number of commands
 * @proc: a struture which contains the command and redirection
 * @envp: the environment variable
 */
void	init_bash_exec(int ac, t_shell *bash)
{
	bash->middle_scommand = ac - 2;
	bash->total_pipes = ac - 1;
	bash->counter = 0;
	bash->env_vars = linked_to_array(bash->env_list);
	if (!bash->env_vars)
	{
		garbage_collector(&bash);
		exit(printf("Error: No environment variables found\n"));
	}
}

int	pipex(int ac, t_command **scommand, t_shell *bash)
{
	int	counter;
	int	ret;

	ret = 0;
	counter = -1;
	init_bash_exec(ac, bash);
	if (ac > 1)
		while (++counter < ac - 1)
			pipe(bash->fd[counter]);
	if (ac == 1)
		ret = pipex_one_cmd(scommand, bash, bash->env_vars->array);
	else if (ac == 2)
	{
		ret = pipex_two_cmd(scommand, bash, bash->env_vars->array);
	}
	else if (ac > 2)
		ret = pipex_three_cmd(scommand, bash, bash->env_vars->array);
	else
		printf("Error : no command input\n");
	if (bash->env_vars)
		free_t_char(&bash->env_vars);
	return (ret);
}
