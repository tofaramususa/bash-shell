/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:21:08 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/15 18:05:16 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
 * close all pipes
 * @proc: struct that have all the variables i use
*/
void	close_pipes(t_shell *proc)
{
	int	x;

	x = -1;
	while (++x < proc->total_pipe)
	{
		close(proc->fd[x][0]);
		close(proc->fd[x][1]);
	}
}

/**
 * pipex_two_cmd: execute and return err_code for two cmd
 * @av: a structure that contains the whole variables
 * @proc: a struture which contains the command and redirection
 * @envp: the environment variable
*/
int	pipex_two_cmd(t_command *av, t_shell *proc, char **envp)
{
	signal(SIGINT, SIG_IGN);
	proc->pid1 = first_process(proc, av, envp); //return process id, perform execution
	proc->pid2 = last_process(proc, av, envp); //return process id, per
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
int	pipex_three_cmd(t_command *av, t_shell *proc, char **envp)
{
	proc->x = 0;
	proc->counter = 0;
	signal(SIGINT, SIG_IGN);
	first_process(proc, av, envp);
	while (proc->counter < proc->middle_cmd)
	{
		middl_process(proc, av, envp, proc->counter + 1);
		proc->counter++;
	}
	proc->pid2 = last_process(proc, av, envp);
	close_pipes(proc);
	proc->counter = -1;
	waitpid(proc->pid2, &proc->error_no, 0);
	while (proc->x < (av->cmd_len - 1))
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
int	pipex(int ac, t_command *scommand, t_shell *bash_ptr)
{
	t_shell	bash;
	int		counter;
	char	**envp;
	int		ret;

	ret = 0;
	bash = *bash_ptr;
	envp = linked_to_array(*bash.env_list);//needs fixing //convert the env to an array for use in the env variable
	bash.middle_scommand = ac - 2;
	bash.total_pipes = ac - 1;
	bash.counter = 0;
	counter = -1;
	if (ac > 1)
		while (++counter < ac - 1)
			pipe(bash.fd[counter]);
	if (ac == 1)
		ret = pipex_one_cmd(scommand, &bash, envp);
	else if (ac == 2)
		ret = pipex_two_cmd(scommand, &bash, envp);
	else if (ac > 2)
		ret = pipex_three_cmd(scommand, &bash, envp);
	else
		printf("Error : no command input\n");
	free_array(envp); //function to free the envp
	return (ret);
}
