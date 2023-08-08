/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:39:19 by tmususa           #+#    #+#             */
/*   Updated: 2023/02/01 17:27:56 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_length;
	size_t	src_length;

	if (!dstsize)
		return (ft_strlen((char *) src));
	dst_length = ft_strlen(dst);
	src_length = ft_strlen((char *) src);
	j = dst_length;
	i = 0;
	if (dst_length >= dstsize)
		return (dstsize + src_length);
	if (dst_length < dstsize - 1 && dstsize > 0)
	{
		while (src[i] && dst_length + i < dstsize - 1)
		{
				dst[j] = src[i];
				i++;
				j++;
		}
		dst[j] = '\0';
	}
	return (dst_length + src_length);
}
