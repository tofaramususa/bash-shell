/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:51:25 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/20 16:36:38 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * search: scan the environment variable for the PATH fro 2d array
 * @envp: the environment variable
*/
int	search(char **envp)
{
	int	x;

	x = -1;
	while (envp[++x])
		if (ft_strnstr(envp[x], "PATH=", 5))
			return (1);
	return (0);
}

int	check_nns(char *str)
{
	int	x;

	x = 0;
	if (!str)
		return (1);
	if (str[x] != '-' || str[x + 1] != 'n')
		return (1);
	while (str[++x])
		if (str[x] != 'n')
			return (1);
	return (0);
}

void	free_one_exec(t_shell *proc, t_command *pipe)
{
	if (pipe->cmd_len > 1)
	{
		free_array(proc->envp);
		free_redirection(pipe);
		ultimate_free(proc, pipe);
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((int)*s1 - *s2);
}

int	check_red_name(char *str)
{
	if ((ft_strcmp(str, ">") == 0 || ft_strcmp(str, "<") == 0 \
	|| ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<<") == 0))
		return (1);
	return (0);
}
