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

#include "words.h"
//START FROM THE BOTTOM

//this function is to return the index to stop  this will be when we encounter another delimiter that is not in a quote bracket
static int get_end_index_sp(const char *s, const char *delimiters, int start) 
{
	t_quote quotes;
	int end;

	quotes.single_q = false;
	quotes.double_q = false;
	end = start;
	while (s[end]) 
	{
		set_quote_flag(&quotes, s[end]); //check each character and if its a quote then change the flag value
		if (array_strchr(delimiters, s[end]) && !quotes.single_q && !quotes.double_q) //stop when we find a space not in quotes
			break;
		end++;
	}
    return (end);
}

//count the number of items we need to allocate memory for in our array
static int	num_words(const char *s, char *delimiters)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (!array_strchr(delimiters,s[i]))
		{
			i = get_end_index_sp(s, delimiters, i);
            count++;
		}
		else
			i++;
	}
	return (count);
}

//discards delimiter characters and takes a substring to fill into the array
static char **remove_spaces(char const *s, char **array, char *delimiters)
{

	int i;
	int start;

	i = 0;
	start = 0;
	while (i < (num_words(s, delimiters)))
	{
		while (s[start] && (array_strchr(delimiters, s[start]))) //skip the spaces
			start++;
		array[i++] = ft_substr(s, start, (get_end_index_sp(s, delimiters, start) - start)); //take the word inbetween the delimiters
		start = get_end_index_sp(s, delimiters, start); //start where we ended
	}
	array[i] = NULL; 
	return (array);
}

char	**ft_space(const char *s)
{
	char	**array;
	char *delimiters;

	delimiters = "\t  \n\r\v\f\b";
	if (!s)
		return (NULL);
	array = (char **) malloc(sizeof(char *) * (num_words(s, delimiters) + 1)); //point of memory allocation
	if (array == NULL)
		return (NULL);
	array = remove_spaces(s, array, delimiters); //split char *s on spaces and produce array
	return (array);
}

