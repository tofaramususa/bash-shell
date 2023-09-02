/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:59:07 by tmususa           #+#    #+#             */
/*   Updated: 2023/09/02 22:09:57 by tmususa          ###   ########.fr       */
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
		if (!array_strchr("\t  \n\r\v\f\b", str[i]))
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

t_token	*ft_tokenise(t_shell *bash, char **str_tokens)
{
	t_token	*tokenlist;
	t_char	*expanded_str;

	expanded_str = (t_char *) malloc(t_char);
	expanded_str->array = expand_array(bash, str_tokens);
	tokenlist = create_token_list(expanded_str);
	if (tokenlist == NULL)
		return (tokenlist);
	if (token_syntax_check(tokenlist) == false)
	{
		g_error_status = 127;
		free_array(str_tokens);
		return (NULL);
	}
	token_quote_removal(tokenlist);
	free_array(str_tokens);
	free_t_char(expanded_str);
	return (tokenlist);
}

int	count_commands(t_token *start, t_token *end)
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

t_compound	*create_compound_node(t_token *start, t_token *end)
{
	t_token		*temp;
	t_token		*temp_end;
	t_compound	*node;
	int			i;

	node = (t_compound *)malloc(sizeof(t_compound));
	if (!node)
		exit(printf("memory allocation failure"));
	node->s_commands = (t_command **)malloc(sizeof(t_command *)
		* (count_commands(start, end) + 1));
	if (!node)
		exit(printf("memory allocation failure"));
	temp = start;
	i = -1;
	while (++i < count_commands(start, end))
	{
		temp_end = temp;
		while (temp_end->next != NULL && temp_end->next != end->next
			&& temp_end->next->type != PIPE)
			temp_end = temp_end->next;
		node->s_commands[i] = create_scmnd_node(temp, temp_end);
		node->s_commands[i]->cmd_len = count_commands(start, end);
		node->s_commands[i]->isfreed = false;
		if (temp_end->next != NULL && temp_end->next != end->next)
			temp = temp_end->next->next;
		else
			temp = NULL;
	}
	node->s_commands[i] = NULL;
	node->cmd_len = count_commands(start, end);
	return (node);
}
