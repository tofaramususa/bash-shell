/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:52:10 by yonamog2          #+#    #+#             */
/*   Updated: 2023/08/27 15:16:19 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * ft_print_echo: print arguments to the terminal
 * @pipe: the structure containint the commands, redirections and args
 * @x: the indexing for the ags
*/
void	ft_print_echo(t_command *pipe, int x)
{
	int	flag;

	flag = 0;
	while (++x < pipe->args_len)
	{
		if ((check_nns(pipe->args[x]) == 0 && flag == 0) || !pipe->args[x])
			continue ;
		if (pipe->args[x + 1] == NULL)
			printf("%s", pipe->args[x]);
		else
			printf("%s ", pipe->args[x]);
		flag = 1;
	}
}

/**
 * ft_echo: will just take a string and print it
 * @pipe: a structure that hold the whole commands and args
*/
void	ft_echo(t_command *pipe, t_shell *proc, char **envp)
{
	if (pipe[proc->scommand_index].args_len == 1)
	{
		printf("\n");
		garbage_collector(proc);
	}
	else if (check_nns(pipe[proc->scommand_index].args[1]) == 0)
	{
		ft_print_echo(&pipe[proc->scommand_index], 1);
		garbage_collector(proc);
	}
	else
	{
		ft_print_echo(&pipe[proc->scommand_index], 0);
		printf("\n");
		garbage_collector(proc);
	}
	exit(0);
}

/**
 * ft_pwd: will print the current directory
*/
void	ft_pwd(t_shell *data, t_command *pipe, char **envp)
{
	char	res[4096];
	char	*pwd;

	pwd = getcwd(res, 4096);
	if (!pwd)
	{
		ft_putstr_fd("Error: sorry dir is deleted or incorrect!\n", 2);
		garbage_collector(data);
		exit(1);
	}
	printf("%s\n", pwd);
	garbage_collector(data);
	exit(0);
}

/**
 * scan_exit_codes: just scan the sargs of exit,
 * @pipe: the structure containin the whole command, args and redirections
*/
int	scan_exit_codes(t_command *pipe)
{
	int	j;

	j = -1;
	while (pipe->args[1][++j])
	{
		if (j == 0 && (pipe->args[1][j] == '+' || pipe->args[1][j] == '-'))
			continue ;
		if (ft_isdigit(pipe->args[1][j]) == 0)
			return (1);
	}
	return (0);
}

/**
 * ft_exit: will print the current directory
 * @pipe: the struct that contains the whold command and instructions
*/
void	ft_exit(t_command *pipe, t_shell *proc)
{
	proc->x = 0;
	if (pipe[proc->scommand_index].args[1] == NULL) //exit only takes one argument
	{
		garbage_collector(proc);//free the redirections, shell and simple commands;
		exit(error_status); //exit
	}
	if (pipe[proc->scommand_index].args[2]) //exit only takes one argument
	{
		write(2, pipe[proc->scommand_index].cmd, ft_strlen(pipe[proc->scommand_index].cmd));
		ft_putstr_fd(": too many arguments\n", 2);
		return ;
	}
	if (scan_exit_codes(&pipe[proc->scommand_index]) == 1) //check for exit codes
	{
		write(2, pipe[proc->scommand_index].cmd, ft_strlen(pipe[proc->scommand_index].cmd));
		ft_putstr_fd(": numeric argument required\n", 2);
		garbage_collector(proc);
		exit(255);
	}
	if (pipe[proc->scommand_index].args[1]) //not sure
		proc->x = (unsigned char)ft_exit_helper(pipe[proc->scommand_index].args[1], pipe, proc);
	garbage_collector(proc);
	exit(proc->x);
}
