/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 03:44:23 by tmususa           #+#    #+#             */
/*   Updated: 2023/09/08 13:56:16 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

t_list	*ft_lstnew(char *key, char *value, int index, int position)
{
	t_list	*node;

	(void)position;
	node = (t_list *)malloc(sizeof(t_list));
	if (node)
	{
		node->key = ft_strdup(key);
		node->value = ft_strdup(value);
		node->index = index;
		node->isfreed = false;
		node->next = NULL;
	}
	free(key);
	free(value);
	return (node);
}
