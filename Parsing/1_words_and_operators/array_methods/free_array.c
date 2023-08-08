/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:23:37 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/06 19:26:32 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arrays.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
			free(array[i++]);
		free(array);
	}
}