/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:30:23 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/27 17:09:16 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_end_index(char *s, char *delimiters, int start)
{
	t_quote	quotes;

	quotes.single_q = false;
	quotes.double_q = false;
	if (s[start] && array_strchr(delimiters, s[start]))
	{
		if (s[start + 1] && (s[start] == s[start + 1]) && s[start] != '|')
			return (start += 2);
		else
			return (start + 1);
	}
	else
	{
		while (s[start])
		{
			set_quote_flag(&quotes, s[start]);
			if (array_strchr(delimiters, s[start]) && !quotes.single_q
				&& !quotes.double_q)
				break ;
			start++;
		}
	}
	return (start);
}

static int	total_tokens(char *s, char *delimiters)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (!array_strchr(delimiters, s[i]))
			i = get_end_index(s, delimiters, i);
		else
		{
			if (s[i + 1] && (s[i] == s[i + 1]) && s[i] != '|')
				i += 2;
			else
				i++;
		}
		count++;
	}
	return (count);
}

static char	**split_on_delim(char *s, char **array, char *delimiters)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (i < (total_tokens(s, delimiters)))
	{
		if (s[start] && array_strchr(delimiters, s[start]))
		{
			if (s[start + 1] && (s[start] == s[start + 1]) && s[start] != '|')
				array[i++] = ft_substr(s, start, 2);
			else
				array[i++] = ft_substr(s, start, 1);
		}
		else
			array[i++] = ft_substr(s, start, get_end_index(s, delimiters, start)
				- start);
		start = get_end_index(s, delimiters, start);
	}
	array[i] = NULL;
	return (array);
}

char	**ft_strtok(char *s)
{
	char	**array;
	char	*delimiters;

	delimiters = "<|>";
	if (!s)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (total_tokens(s, delimiters) + 1));
	if (array == NULL)
		return (NULL);
	array = split_on_delim(s, array, delimiters);
	return (array);
}
