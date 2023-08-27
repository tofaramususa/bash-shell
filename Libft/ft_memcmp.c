/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:10:03 by tmususa           #+#    #+#             */
/*   Updated: 2023/02/01 17:26:54 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*first = s1;
	const unsigned char	*second = s2;

	while (n--)
	{
		if (*first != *second)
			return (*first - *second);
	first++;
	second++;
	}
	return (0);
}
