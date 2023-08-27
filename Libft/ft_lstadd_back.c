/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 04:31:42 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/27 15:16:01 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *add)
{
	t_list	*to_last;

	if (*lst)
	{
		to_last = ft_lstlast(*lst);
		to_last->next = new;
	}
	else
		*lst = new;
}
