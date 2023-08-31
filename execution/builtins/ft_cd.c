/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 11:45:06 by yonamog2          #+#    #+#             */
/*   Updated: 2023/08/30 16:37:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/**
 * ft_cd_util: check if current pwd exits,, then change dir 
 * and replace env, accordingly
 * @pipe: a struct containing the whole command
 * @pwd: string of the current pwd 
 * @proc: structure containing the whole variables
*/
static int	ft_cd_util(t_command **pipe, char *pwd, t_shell *proc)
{
	char	*tmp;

	if (chdir((*pipe)->args->array[1]) == 0)
	{
		if (pwd)
		{
			tmp = ft_strjoin("OLDPWD=", pwd);
			check_and_replace(proc->env_list, tmp);
			free(tmp);
		}
		pwd = getcwd(proc->pwd, 1024);
		tmp = ft_strjoin("PWD=", pwd);
		if (pwd)
		{
			proc->x = check_and_replace(proc->env_list, tmp);
			return (free(tmp), proc->x);
		}
		ft_putstr_fd("cd: error retrieving current directory: getcwd: \
		cannot access parent directories: No such file or directory\n", 2);
		return (1);
	}
	else
		return (write(1, (*pipe)->args->array[1], \
		ft_strlen((*pipe)->args->array[1])), perror(" "), 1);
	return (0);
}

/**
 * ft_cd_util_3: check if home is set and change the dir to home
 * and update oldpwd and pwd accordingly
 * @pipe: a struct containing the whole command
 * @pwd: string of the current pwd 
 * @proc: structure containing the whole variables
*/
static	int	ft_cd_util_3(char *pwd, t_shell *proc)
{
	char	*tmp;

	if (pwd)
	{
		tmp = ft_strjoin("OLDPWD=", pwd);
		check_and_replace(proc->env_list, tmp);
		if (tmp)
			free(tmp);
	}
	pwd = getcwd(proc->pwd, 1024);
	if (pwd)
	{
		tmp = ft_strjoin("PWD=", pwd);
		proc->x = check_and_replace(proc->env_list, tmp);
		return (safe_free(tmp), proc->x);
	}
	return (1);
}

/**
 * ft_cd_util_2: check if home is set and change the dir to home
 * and update oldpwd and pwd accordingly
 * @pipe: a struct containing the whole command
 * @pwd: string of the current pwd 
 * @proc: structure containing the whole variables
*/
static	int	ft_cd_util_2(char *pwd, t_shell *proc)
{
	char	*tmp;

	if (chdir(ft_getenv(proc->env_list, "HOME")) == 0)
		return (ft_cd_util_3(pwd, proc));
	else
	{
		tmp = ft_getenv(proc->env_list, "HOME");
		if (tmp == NULL)
			ft_putstr_fd("cd: HOME not set\n", 2);
		else
		{
			write(2, tmp, ft_strlen(tmp));
			perror(" ");
		}
		return (safe_free(tmp), 1);
	}
	return (0);
}

/**
 * ft_cd: changed  the current working directory
 * @pipe: the struct that contains the whold command and instructions
*/
int	ft_cd(t_command **pipe, t_shell *proc)
{
	char	*pwd;

	pwd = getcwd(proc->pwd, 1024); //get directory
	proc->x = 0; //this is temporary exit status
	if (pipe[proc->scommand_index]->args->array[1])
		proc->x = ft_cd_util(&pipe[proc->scommand_index], pwd, proc); //check if theres argument after cd
	else if (pipe[proc->scommand_index]->args->array[1] == NULL)
		proc->x = ft_cd_util_2(pwd, proc); //if nothing then go to home directory
	if ((*pipe)->cmd_len > 1) //if more than 1 command free everything
	{
		garbage_collector(&proc);
	}
	return (proc->x); // then return exit status
}
