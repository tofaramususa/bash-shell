/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:10:40 by tmususa           #+#    #+#             */
/*   Updated: 2023/01/22 17:44:09 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

int	ft_tolower(int c)
{
	unsigned char	ch;

	ch = (unsigned char ) c;
	if (ch >= 'A' && ch <= 'Z')
		ch += 32;
	return (ch);
}
