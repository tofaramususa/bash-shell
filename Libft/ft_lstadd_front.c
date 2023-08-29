/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 04:08:35 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/27 15:16:01 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *add)
{
	if (lst != NULL && add != NULL)
	{
		add->next = *lst;
		*lst = add;
	}
}
