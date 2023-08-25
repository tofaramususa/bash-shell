/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 04:44:50 by tmususa           #+#    #+#             */
/*   Updated: 2023/01/31 14:08:59 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*new_node;

	if (!lst || !f || !del)
		return (NULL);
	newlist = ft_lstnew(f(lst->content));
	if (!newlist)
		return (NULL);
	new_node = newlist;
	lst = lst->next;
	while (lst)
	{
		newlist->next = ft_lstnew(f(lst -> content));
		if (!newlist->next)
		{
			ft_lstclear(&new_node, del);
			return (NULL);
		}
		newlist = newlist->next;
		lst = lst->next;
	}
	newlist->next = NULL;
	return (new_node);
}
