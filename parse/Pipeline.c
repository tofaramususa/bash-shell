/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tofaramususa <tofaramususa@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:59:07 by tmususa           #+#    #+#             */
/*   Updated: 2023/11/16 20:51:59 by tofaramusus      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

bool	check_line(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (false);
	if (check_unmatched_quotes(str) == true)
	{
		return (printf("unbalanced quotes\n"), false);
	}
	while (str[++i])
	{
		if (!array_strchr("\t  \n\v\f\b", str[i]))
			break ;
	}
	if (str[i] == '\0')
	{
		return (false);
	}
	return (true);
}

char	**ft_split_on_delims(char *str)
{
	char	**temp_tokens;
	char	**final_tokens;
	char	**next_tokens;
	int		i;

	i = -1;
	temp_tokens = ft_space(str);
	if (temp_tokens == NULL)
	{
		return (NULL);
	}
	while (temp_tokens[++i] != NULL)
	{
		if (i == 0)
			final_tokens = ft_strtok(temp_tokens[i]);
		else
		{
			next_tokens = ft_strtok(temp_tokens[i]);
			final_tokens = append_array(final_tokens, next_tokens);
			free_array(next_tokens);
		}
	}
	return (free_array(temp_tokens), final_tokens);
}

bool	ft_tokenise(t_shell *bash, char **str_tokens)
{
	if (!str_tokens)
		return (false);
	bash->tokenlist = create_token_list(str_tokens, bash);
	free_array(str_tokens);
	if (bash->tokenlist == NULL)
		return (bash->tokenlist);
	if (token_syntax_check(bash->tokenlist) == false)
	{
		g_error_status = 127;
		return (false);
	}
	token_quote_removal(bash->tokenlist);
	return (true);
}

int	count_pipes(t_token *start, t_token *end)
{
	int		i;
	t_token	*temp;

	temp = start;
	i = 1;
	while (temp && temp->value != NULL && temp != end->next)
	{
		if (temp->type == PIPE)
			i++;
		temp = temp->next;
	}
	return (i);
}

void	create_compound_node(t_token *start, t_token *end, t_shell *bash,
		t_compound *node)
{
	t_token	*temp;
	t_token	*temp_end;
	int		i;

	node->s_commands = (t_command **)malloc(sizeof(t_command *)
			* (count_pipes(start, end) + 1));
	if (!node->s_commands)
		collect_and_exit(bash, "memory allocation failure");
	temp = start;
	i = -1;
	while (++i < count_pipes(start, end))
	{
		temp_end = temp;
		while (temp_end->next != NULL && temp_end->next != end->next
			&& temp_end->next->type != PIPE)
			temp_end = temp_end->next;
		node->s_commands[i] = create_scmnd_node(temp, temp_end);
		node->s_commands[i]->cmd_len = count_pipes(start, end);
		if (temp_end->next != NULL && temp_end->next != end->next)
			temp = temp_end->next->next;
		else
			temp = NULL;
	}
	node->s_commands[i] = NULL;
}
