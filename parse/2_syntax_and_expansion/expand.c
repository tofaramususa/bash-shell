/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:05:52 by tmususa           #+#    #+#             */
/*   Updated: 2023/09/08 17:50:45 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static char	*get_env_var(t_shell *bash, char *str, int start)
{
	char	*search_var;
	char	*env_var;

	env_var = NULL;
	search_var = ft_substr(str, start + 1, get_search_var_end(str, start)
			- start);
	if (search_var && search_var[0] == '?' && search_var[1] == '\0')
	{
		env_var = ft_itoa(g_error_status);
	}
	else
		env_var = ft_strdup(ft_getenv(bash->env_list, search_var));
	if (env_var == NULL)
	{
		safe_free(search_var);
		return (ft_strdup(""));
	}
	if (search_var)
	{
		safe_free(search_var);
	}
	return (env_var);
}

static char	*new_expanded_str(t_shell *bash, char *str)
{
	int		i;
	char	*expanded_str;
	char	*temp_str;
	int		count;

	i = 0;
	count = 0;
	expanded_str = NULL;
	temp_str = NULL;
	while (str[i] && ++count)
	{
		if (str[i] == '$' && !array_strchr("\" /~%^{}:;''\0'", str[i + 1]))
		{
			temp_str = get_env_var(bash, str, i);
			i = get_search_var_end(str, i) + 1;
		}
		else
		{
			temp_str = ft_substr(str, i, get_end_index_expan(str, i) - i);
			i = get_end_index_expan(str, i);
		}
		expanded_str = strjoin_new_var(temp_str, expanded_str, count);
	}
	return (expanded_str);
}

char	*final_expanded_str(t_shell *bash, char *str)
{
	char	*final_str;
	char	*expand_temp;

	final_str = ft_strdup(str);
	while (needs_expansion(final_str) == true)
	{
		expand_temp = new_expanded_str(bash, final_str);
		safe_free(final_str);
		final_str = ft_strdup(expand_temp);
		safe_free(expand_temp);
	}
	safe_free(str);
	return (final_str);
}

static t_token	*expand_new_token_node(char *arg)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (node)
	{
		node->value = ft_strdup(arg);
		node->type = WORD;
		node->isfreed = false;
		node->next = NULL;
	}
	return (node);
}

void	expand_token(t_token **tokenlist, char *str, t_shell *bash)
{
	char	**temp;
	int		index;
	char	*expanded_str;

	expanded_str = ft_strdup(str);
	expanded_str = final_expanded_str(bash, expanded_str);
	temp = ft_space(expanded_str);
	index = -1;
	while (temp[++index])
	{
		if (ft_strcmp("", temp[index]) == 0)
			continue ;
		add_token_node(tokenlist, expand_new_token_node(temp[index]));
	}
	free_array(temp);
	safe_free(expanded_str);
}
