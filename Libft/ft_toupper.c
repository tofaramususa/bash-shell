/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:10:40 by tmususa           #+#    #+#             */
/*   Updated: 2023/01/22 17:50:25 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

int	ft_toupper(int c)
{
	unsigned char	ch;

	ch = (unsigned char ) c;
	if (ch >= 'a' && ch <= 'z')
		ch -= 32;
	return (ch);
}
