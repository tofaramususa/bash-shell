/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_one_cmd_proccess.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 13:03:36 by yonamog2          #+#    #+#             */
/*   Updated: 2023/09/02 21:54:07 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/**
 * check_built_ins_and_exexute_one_cmd: check if the
 * command is one of the built ins
 * and execute that but now its for one command only
 * @proc: struct that have all the variables i use
 * @av: structure of the commands
 * @envp: 2d array conataining the environment variables
 */
void	check_built_ins_and_exexute_one_cmd(t_shell *proc, t_command **av,
		char **envp)
{
	(void)envp;
	if (proc->check == 1)
		ft_exit(av, proc);
	else if (proc->check == 2)
		ft_echo(av, proc);
	else if (proc->check == 3)
		ft_cd(av, proc);
	else if (proc->check == 4)
		ft_pwd(proc);
	else if (proc->check == 5)
		ft_env_print_linked(proc);
	else if (proc->check == 6)
		ft_export_print_linked(av, proc);
	else if (proc->check == 7)
		ft_unset(av, proc);
	exit(1);
}

void	check_and_execute(t_shell *proc, t_command **av, char **envp, char *tmp)
{
	if ((*av)->cmd && tmp && (*av)->cmd[0])
	{
		execve(tmp, (*av)->args->array, envp);
		free_func_one_cmd(av, proc);
	}
	else
		cmd_not_found(av, proc, 0);
}

/**
 * one_cmd_process: a function that execute one command
 * @proc: struct that have all the variables i use
 * @av: structure of the commands
 * @envp: 2d array conataining the environment variables
 */
void	one_cmd_process(t_shell *proc, t_command **av, char **envp)
{
	char	*tmp;

	proc->process_id = fork();
	if (proc->process_id < 0)
		terminate("fork", proc);
	if (proc->process_id == 0)
	{
		if ((*av)->total_redirs > 0)
			red_one_cmd(av, proc);
		if ((*av)->cmd == NULL)
		{
			garbage_collector(&proc);
			exit(0);
		}
		proc->check = ft_check_builtin((*av)->cmd);
		if (proc->check > 0)
			check_built_ins_and_exexute_one_cmd(proc, av, envp);
		tmp = get_command(proc, envp, (*av)->cmd);
		check_and_execute(proc, av, envp, tmp);
	}
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

/**
 * pipex_one_cmd: execute and return err_code for one cmd
 * @av: a structure that contains the whole variables
 * @proc: a struture which contains the command and redirection
 * @envp: the environment variable
 */
int	pipex_one_cmd(t_command **av, t_shell *proc, char **envp)
{
	proc->scommand_index = 0;
	if (av[0]->cmd && ft_strcmp(av[0]->cmd, "cd") == 0)
		return (do_operation(proc, av), ft_cd(av, proc));
	else if (av[0]->cmd && ft_strcmp(av[0]->cmd, "exit") == 0)
	{
		do_operation(proc, av);
		ft_exit(av, proc);
		return (1);
	}
	else if (av[0]->cmd && ft_strcmp(av[0]->cmd, "unset") == 0)
		return (do_operation(proc, av), ft_unset(av, proc));
	else if (av[0]->cmd && ft_strcmp(av[0]->cmd, "export") == 0)
		return (do_operation(proc, av), ft_export_print_linked(av, proc));
	else
		return (set_signal_exe(av, proc, envp));
	return (0);
}

static char	*check_for_access(t_shell *proc, char **envp, char **path_split,
		char *s)
{
	char	*path;
	char	*result;

	result = NULL;
	while (path_split[++proc->x] && (search_for_path(envp) == 1))
	{
		path = ft_strjoin(path_split[proc->x], "/");
		result = ft_strjoin(path, s);
		if (access(result, 0) == 0)
		{
			safe_free(path);
			return (result);
		}
		safe_free(result);
		safe_free(path);
	}
	return (NULL);
}

char	*get_command(t_shell *proc, char **envp, char *s)

{
	char **path_split;
	char *result;

	proc->x = -1;
	if (!s)
		return (NULL);
	result = NULL;
	if (ft_strnstr(s, "/", ft_strlen(s)) || ft_strcmp(s, ".") == 0
		|| ft_strcmp(s, "..") == 0 || s[0] == '\0')
		return (s);
	if (search_for_path(envp) == 0)
		return (NULL);
	while (envp[++proc->x])
	{
		if (ft_strncmp(envp[proc->x], "PATH=", 5) == 0)
			break ;
	}
	path_split = ft_split(envp[proc->x] + 5, ':');
	proc->x = -1;
	result = check_for_access(proc, envp, path_split, s);
	free_array(path_split);
	return (result);
}