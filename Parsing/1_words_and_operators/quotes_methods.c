/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_methods.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:19:29 by tmususa           #+#    #+#             */
/*   Updated: 2023/08/05 21:45:36 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "words.h"

// check our line for unbalanced quotes and return an error
bool check_unmatched_quotes(const char *str)
{
	bool single_quote = false;
	bool double_quote = false;

	while(*str)
	{
		if(*str == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (*str == '"' && !single_quote)
			double_quote = !double_quote;
		str++;
	}
	return (single_quote || double_quote);
}
//change the value of the quote flag if character is a quote character
void set_quote_flag(t_quote *value, char c)
{
	if(c == '\'')
		value->single_q = !value->single_q;
	else if(c == '"')
		value->double_q = !value->double_q;
}


