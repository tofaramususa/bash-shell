/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_methods.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:19:29 by tmususa           #+#    #+#             */
/*   Updated: 2023/09/08 13:52:51 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

bool	check_unmatched_quotes(char *str)
{
	bool	single_quote;
	bool	double_quote;

	single_quote = false;
	double_quote = false;
	while (*str)
	{
		if (*str == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (*str == '"' && !single_quote)
			double_quote = !double_quote;
		str++;
	}
	return (single_quote || double_quote);
}

void	set_quote_flag(t_quote *value, char c)
{
	if (c == '\'' && value->double_q == false)
		value->single_q = !value->single_q;
	else if (c == '"' && value->single_q == false)
		value->double_q = !value->double_q;
}

void	safe_free(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}
