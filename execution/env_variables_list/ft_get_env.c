/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:07:03 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/19 14:30:52 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * ft_getenv: variable that check for the variable name from the linked list
 * and return the values
 * @head: the head of the linked list
 * @str: the variable name
*/

char	*ft_getenv(t_list *head, char *str)
{
	t_list	*tmp;
	char	*tmp_val;

	tmp = head;
	tmp_val = ft_strjoin(str, "=");
	while (tmp)
	{
		if (ft_strcmp(tmp->key, tmp_val) == 0)
			return (free_str(tmp_val), tmp->value);
		tmp = tmp->next;
	}
	free_str(tmp_val);
	return (NULL);
}

/**
 * get_next_line: simple function to get a line from STDIN
 * @fd: the file discriptor to read from
*/
char	*get_next_line(int fd)
{
	char	*copy;
	char	*tmp;

	if (fd < 0)
		return (NULL);
	copy = ft_calloc(sizeof(char), 1000000);
	if (!copy)
		return (NULL);
	tmp = copy;
	while (read(fd, tmp, 1))
		if (*(tmp++) == '\n')
			break ;
	if (copy[0] == '\0')
		return (free_str(copy), NULL);
	else
		return (copy);
}
