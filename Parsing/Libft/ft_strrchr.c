/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:57:52 by tmususa           #+#    #+#             */
/*   Updated: 2023/01/31 15:14:57 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = ft_strlen((char *) s);
	while (i >= 0)
	{
		if (s[i] == (char ) c)
			return (((char *)&s[i]));
		i--;
	}
	if (c == 0)
		return (((char *) &s[i]));
	return (NULL);
}
