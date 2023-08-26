/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:05:52 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/13 21:02:58 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Parse.h"

bool	needs_expansion(char *str)
{
	t_quote	quotes;
	int		start;

	start = 0;
	quotes.single_q = false;
	quotes.double_q = false;
	while (str[start] != '\0')
	{
		set_quote_flag(&quotes, str[start]);
		if (str[start] == '$' && !quotes.single_q && !array_strchr("\" '/~%^{}:; '\0'",
				str[start + 1]))
			return (true);
		start++;
	}
	return (false);
}

int	get_search_var_end(char *str, int start)
{
	if (str[start + 1] && array_strchr("$?", str[start + 1]))
		return (start + 1);
	start++;
	while (str[start])
	{
		if (array_strchr("\"' /~%^{}:;$'\0'", str[start + 1]))
			break ;
		start++;
	}
	return (start);
}
int	get_end_index_expan(char *str, int start)
{
	t_quote	quotes;

	quotes.single_q = false;
	quotes.double_q = false;
	while (str[start])
	{
		set_quote_flag(&quotes, str[start]);
		if (str[start] == '$' && !quotes.single_q && !array_strchr("\" ' /~%^{}:;'\0'",
				str[start + 1]))
			break ;
		start++;
	}
	return (start);
}

char	*strjoin_new_var(char *temp_str, char *expanded_str, int count)
{
	char	*temp;

	temp = NULL;
	if (count > 1 && expanded_str)
	{
		temp = ft_strjoin(expanded_str, temp_str);
		if (temp)
			freeandnullify(expanded_str);
	}
	else
		temp = ft_strdup(temp_str);
	if (temp)
		freeandnullify(temp_str);
	return (temp);
}
