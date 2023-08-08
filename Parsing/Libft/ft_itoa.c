/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:31:47 by tmususa           #+#    #+#             */
/*   Updated: 2023/01/29 09:06:33 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nbr_len(int n)
{
	int	len;

	if (n <= -2147483648)
	{
		len = 11;
		return (len);
	}
	len = 0;
	if (n < 0)
	{
			n *= -1;
			len += 1;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			length;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	length = nbr_len(n);
	if (!length)
		length++;
	str = (char *) malloc(sizeof(char) * (length + 1));
	if (str == NULL)
		return (NULL);
	str[length] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	if (n == 0)
		str[0] = '0';
	while (n)
	{
		str[--length] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
