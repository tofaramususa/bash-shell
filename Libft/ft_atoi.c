/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:16:16 by tmususa           #+#    #+#             */
/*   Updated: 2023/09/09 20:05:24 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	rs;
	int		sg;

	i = 0;
	rs = 0;
	sg = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sg = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		rs = rs * 10 + str[i] - '0';
		if (rs * sg > 2147483648)
			return (-1);
		else if (rs * sg < -2147483648)
			return (0);
		i++;
	}
	return (rs * sg);
}
