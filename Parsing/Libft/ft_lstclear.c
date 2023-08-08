/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 04:39:54 by tmususa           #+#    #+#             */
/*   Updated: 2023/01/31 14:56:21 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*listnode;
	t_list	*tmp;

	listnode = *lst;
	while (listnode)
	{
		tmp = listnode->next;
		ft_lstdelone(listnode, del);
		listnode = tmp;
	}
	*lst = NULL;
}
