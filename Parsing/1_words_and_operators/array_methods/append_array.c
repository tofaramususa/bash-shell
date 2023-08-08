/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:27:36 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/06 19:47:23 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arrays.h"


static char **ft_subarray(char **final, const char **s1, const char **s2)
{
    // if(!final  || !s1 || !s2)
    //     return NULL;
    int i;
    int j;
    int total_rows;

    i = -1;
    j = -1;
    while (++i < ft_array_len(s1))
    {
        final[++j] = ft_strdup((char *)s1[i]);
        // if(final[j] == NULL)
        //     do something
    }
    i = -1;
    while (++i < ft_array_len(s2))
        final[++j] = ft_strdup((char *)s2[i]);
    total_rows = ft_array_len(s1) + ft_array_len(s2);
    final[total_rows] = NULL;
    return (final);
}

char **append_array(const char  **s1, const char **s2)
{
    int s1_rows;
    int s2_rows;
    char **final;

    s1_rows = 0;
    s2_rows = 0;
    // if (!s1 || !s2)
    //     return (NULL);
    s1_rows = ft_array_len(s1);
    s2_rows = ft_array_len(s2);
    final = (char **) malloc((s1_rows + s2_rows + 1) * sizeof(char *));
    // if (final == NULL)
    //     return NULL;
    final = ft_subarray(final, s1, s2);
    return (final);
}