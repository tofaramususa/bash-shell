/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:07:03 by yonamog2          #+#    #+#             */
/*   Updated: 2023/09/08 13:51:33 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

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
	if (str)
		tmp_val = ft_strjoin(str, "=");
	while (tmp)
	{
		if (ft_strcmp(tmp->key, tmp_val) == 0)
			return (safe_free(tmp_val), tmp->value);
		tmp = tmp->next;
	}
	if (tmp_val)
		safe_free(tmp_val);
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
		return (safe_free(copy), NULL);
	else
		return (copy);
}
