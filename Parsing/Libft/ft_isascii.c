/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:23:36 by tmususa           #+#    #+#             */
/*   Updated: 2023/01/17 05:58:48 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int as)
{
	return ((as <= 127) && (as >= 0));
}
