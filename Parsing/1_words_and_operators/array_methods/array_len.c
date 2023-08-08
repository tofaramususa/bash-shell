/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:18:42 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/06 19:44:28 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arrays.h"

int ft_array_len(const char **str)
{
    int str_rows;

    str_rows = 0;

    // if (!str)
    //   return (NULL);
    while (str[str_rows] != NULL)
        str_rows++;
    return(str_rows);
}
