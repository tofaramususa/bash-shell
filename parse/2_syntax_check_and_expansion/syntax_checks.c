/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:12:17 by tmususa           #+#    #+#             */
/*   Updated: 2023/09/03 20:49:28 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static bool	is_close_paren_first(t_token *headtoken)
{
	t_token	*temp2;

	temp2 = headtoken;
	while (temp2)
	{
		if (temp2->type == CLOSE_PAREN)
			return (false);
		if (temp2->type == OPEN_PAREN)
			break ;
		temp2 = temp2->next;
	}
	return (true);
}
static bool	check_parens_match(t_token *headtoken)
{
	t_token	*temp;
	int		stack;

	temp = headtoken;
	stack = 0;
	while (temp)
	{
		if (temp->type == OPEN_PAREN)
			stack += 1;
		if (temp->type == CLOSE_PAREN)
			stack -= 1;
		temp = temp->next;
	}
	if (stack != 0)
		printf("Bash: Parenthesis do not match\n");
	return (stack == 0);
}

static bool	check_for_background(t_token *headtoken)
{
	t_token	*temp;

	temp = headtoken;
	while (temp)
	{
		if (ft_strcmp(temp->value, "&") == 0)
			return (printf("Bash: background processes not supported %s\n",
					temp->value), false);
		temp = temp->next;
	}
	return (true);
}

static bool	parens_sytnax(t_token *headtoken)
{
	t_token	*temp;

	temp = headtoken;
	while (temp && temp->next != NULL)
	{
		if (temp->type == OPEN_PAREN && !(temp->next->type == WORD
				|| temp->next->type == REDIR || temp->next->type == OPEN_PAREN))
			return (printf("Bash: syntax error near unexpected token %s\n",
					temp->value), false);
		if (temp->type == CLOSE_PAREN && (temp->next->type == OPEN_PAREN
				|| temp->next->type == WORD || temp->next->type == PIPE
				|| temp->next->type == REDIR))
			return (printf("Bash: syntax error near unexpected token %s\n",
					temp->value), false);
		if (temp->type == PIPE && (temp->next->type == OPEN_PAREN
				|| temp->next->type == CLOSE_PAREN))
			return (printf("Bash: syntax error near unexpected token `%s'\n",
					temp->value), false);
		if ((temp->type == WORD && temp->next->type == OPEN_PAREN))
			return (printf("Bash: syntax error near unexpected token `%s'\n",
					temp->value), false);
		temp = temp->next;
	}
	return (true);
}

static bool	check_sytnax(t_token *headtoken)
{
	t_token	*temp;

	temp = headtoken;
	if (temp && (temp->type == PIPE || temp->type == AND || temp->type == OR))
	{
		return (printf("Bash: syntax error near unexpected token `%s'\n",
				temp->value), false);
	}
	while (temp && temp->next != NULL)
	{
		if (temp->type == REDIR && temp->next->type != WORD)
			return (printf("Bash: syntax error near unexpected token `%s'\n",
					temp->value), false);
		if ((temp->type == PIPE || temp->type == AND || temp->type == OR)
			&& !(temp->next->type == WORD || temp->next->type == REDIR
				|| temp->next->type == OPEN_PAREN))
			return (printf("Bash: syntax error near unexpected token `%s'\n",
					temp->value), false);
		temp = temp->next;
	}
	if (temp->next == NULL)
	{
		if (temp->type != WORD && temp->type != CLOSE_PAREN)
			return (printf("Bash: syntax error near unexpected token `newline'\n"),
					false);
	}
	return (true);
}

bool	token_syntax_check(t_token *headtoken)
{
	if (!headtoken)
		return (false);
	if (is_close_paren_first(headtoken) == false
		|| check_parens_match(headtoken) == false
		|| check_for_background(headtoken) == false
		|| parens_sytnax(headtoken) == false)
		return (false);
	if (check_sytnax(headtoken) == false)
		return (false);
	return (true);
}
