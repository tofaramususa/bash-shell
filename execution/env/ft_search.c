/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:51:25 by yonamog2          #+#    #+#             */
/*   Updated: 2023/09/08 13:51:39 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/**
 * search: scan the environment variable for the PATH fro 2d array
 * @envp: the environment variable
 */
int	search_for_path(char **envp)
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
