/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:33:31 by tmususa           #+#    #+#             */
/*   Updated: 2023/01/22 16:48:46 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int n, size_t value)
{
	unsigned char	*bp;

	bp = (unsigned char *) b;
	while (value--)
	{
		*bp = (unsigned char) n;
		bp++;
	}
	return (b);
}
