/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_methods.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:54:29 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/12 18:23:57 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../Parse.h"

char **dup_array(char **src)
{
    int num_words;
    char **dest;
    int i;

    num_words = ft_array_len(src);
    dest = (char **) malloc((num_words + 1) * sizeof(char *));
    if (!dest)
        return (NULL);
    i = -1;
    while(++i < num_words)
        dest[i] = ft_strdup(src[i]);
    dest[i] = NULL;
    return (dest);
}

int ft_array_len(char **str)
{
    int str_rows;

    str_rows = 0;

    // if (!str)
    //   return (NULL);
    while (str[str_rows] != NULL)
        str_rows++;
    return(str_rows);
}

bool	array_strchr(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (c == s[i])
			return (true);
		i++;
	}
	if ((char) c == '\0')
		return (true);
	return (false);
}

void	free_array(char **array)
{
	int	i;

	i = -1;
	if (array)
	{
		while (array[++i])
			free_str(array[i]);
		free(array);
	}
}
