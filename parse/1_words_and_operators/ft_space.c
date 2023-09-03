/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:40:13 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/04 17:45:32 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static int	get_end_index_sp(char *s, char *delimiters, int start)
{
	t_quote	quotes;
	int		end;

	quotes.single_q = false;
	quotes.double_q = false;
	end = start;
	while (s[end])
	{
		set_quote_flag(&quotes, s[end]);
		if (array_strchr(delimiters, s[end]) && !quotes.single_q
			&& !quotes.double_q)
			break ;
		end++;
	}
	return (end);
}

static int	num_words(char *s, char *delimiters)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (!array_strchr(delimiters, s[i]))
		{
			i = get_end_index_sp(s, delimiters, i);
			count++;
		}
		else
			i++;
	}
	return (count);
}

static char	**remove_spaces(char *s, char **array, char *delimiters)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (i < (num_words(s, delimiters)))
	{
		while (s[start] && (array_strchr(delimiters, s[start])))
			start++;
		array[i++] = ft_substr(s, start, (get_end_index_sp(s, delimiters, start)
				- start));
		start = get_end_index_sp(s, delimiters, start);
	}
	array[i] = NULL;
	return (array);
}

char	**ft_space(char *s)
{
	char	**array;
	char	*delimiters;

	delimiters = "\t  \n\v\f\b";
	if (!s)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (num_words(s, delimiters) + 1));
	if (array == NULL)
		return (NULL);
	array = remove_spaces(s, array, delimiters);
	return (array);
}
