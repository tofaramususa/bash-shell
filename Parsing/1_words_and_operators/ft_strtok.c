/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:30:23 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/06 20:47:31 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "words.h"
//START FROM THE BOTTOM


// for our ft_substr we need a length value so if its a  >> or << it will be 2 and if only < > | its one
// if it is word we need to get the length to when we need stop and we have found a delimiter not inside the quotes
//the difference of the end returned and the initial start we had gets the len.
int get_end_index(const char *s, const char *delimiters, int start) 
{
	t_quote quotes;

	quotes.single_q = false;
	quotes.double_q = false;
	if (s[start] && ft_strchr(delimiters, s[start]))
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
			if (ft_strchr(delimiters, s[start]) && !quotes.single_q && !quotes.double_q)
				break;
			start++;
		}
	}
    return (start);
}

//we need to count the total tokens including the delimiters found
static int	total_tokens(const char *s, const char *delimiters)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (!array_strchr(delimiters, s[i]))
			 i =get_end_index(s, delimiters, i);
		else
		{
			if (s[i + 1] && (s[i] == s[i + 1]) && s[i] != '|') //if we find a redirection < or > we need to check the next char if its the same then its a heredoc or append
					i+= 2;
			else
				i++;
		}
			count++;
	}
	return (count);
}


static char **split_on_delim(char const *s, char **array, const char *delimiters)
{
	int i;
	int start;

	i = 0;
	start = 0;
	while (i < (total_tokens(s, delimiters)))
	{
		if (s[start] && array_strchr(delimiters, s[start]))
        {
            if (s[start + 1] && (s[start] == s[start + 1]) && s[start] != '|')
                array[i++] =  ft_substr(s, start, 2);
            else
                array[i++] = ft_substr(s, start,  1);
        }
		else
			array[i++] = ft_substr(s, start,get_end_index(s, delimiters, start) - start); //get_end_index - start gets our length for the ft_substr
		start = get_end_index(s, delimiters, start); //start at the end 
	}
	array[i] = NULL; //end our array
	return (array);
}

char	**ft_strtok(char const *s)
{
	char	**array;
	const char	*delimiters;

	delimiters = "<|>"; //our delimiters to seperate on
	if (!s)
		return (NULL);
	array = (char **) malloc(sizeof(char *) * (total_tokens(s, delimiters) + 1)); //point of memory allocation
	if (array == NULL)
		return (NULL);
	array = split_on_delim(s, array, delimiters);
	return (array);
}