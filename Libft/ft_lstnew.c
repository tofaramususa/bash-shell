/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 03:44:23 by tmususa           #+#    #+#             */
/*   Updated: 2023/01/29 10:07:09 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

t_list	*ft_lstnew(char *key, char *value, int index, int position)
{
	t_list	*node;

	(void)position;
	node = malloc (sizeof(t_list));
	if (node)
	{
		node->key = key;
		node->value = value;
		node->index = index;
		node->next = NULL;
	}	
	return (node);
}

