/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:07:06 by tmususa           #+#    #+#             */
/*   Updated: 2023/09/08 20:16:57 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static int	count_chars(char *str)
{
	int		i;
	int		count;
	t_quote	quotes;

	quotes.single_q = false;
	quotes.double_q = false;
	i = -1;
	count = 0;
	while (str[++i])
	{
		set_quote_flag(&quotes, str[i]);
		if ((str[i] == '"' && !quotes.single_q) || (str[i] == '\''
				&& !quotes.double_q))
			continue ;
		count++;
	}
	return (count);
}

char	*remove_quotes(char *str, int in)
{
	char	*new_str;
	int		i;
	int		j;
	t_quote	quotes;

	quotes.single_q = false;
	quotes.double_q = false;
	i = -1;
	j = 0;
	new_str = (char *)malloc(sizeof(char *) * (count_chars(str) + 1));
	while (str[++i])
	{
		set_quote_flag(&quotes, str[i]);
		if ((str[i] == '"' && !quotes.single_q) || (str[i] == '\''
				&& !quotes.double_q))
			continue ;
		new_str[j++] = str[i];
	}
	new_str[j] = '\0';
	if (in == 1)
		safe_free(str);
	return (new_str);
}

void	token_quote_removal(t_token *tokenlist)
{
	t_token	*temp;

	temp = tokenlist;
	while (temp)
	{
		if (temp->type == REDIR && ft_strcmp(temp->value, "<<") == 0
			&& temp->next)
		{
			temp = temp->next->next;
			continue ;
		}
		if (temp->type == WORD)
			temp->value = remove_quotes(temp->value, 1);
		temp = temp->next;
	}
}
