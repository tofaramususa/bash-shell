/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:05:52 by tmususa           #+#    #+#             */
/*   Updated: 2023/09/02 20:06:26 by tmususa          ###   ########.fr       */
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
	int start;
	char *expanded_str;
	char *temp_str;
	int count;

	start = 0;
	count = 0;
	expanded_str = NULL;
	temp_str = NULL;

	while (str[start] && ++count)
	{
		if (str[start] == '$' && !array_strchr("\" /~%^{}:;''\0'", str[start
				+ 1]))
		{
			temp_str = get_env_var(bash, str, start);
			start = get_search_var_end(str, start) + 1;
		}
		else
		{
			temp_str = ft_substr(str, start, get_end_index_expan(str, start)
				- start);
			start = get_end_index_expan(str, start);
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
	return (final_str);
}

char	**expand_array(t_shell *bash, char **str)
{
	char	**expanded_str;
	int		i;

	i = 0;
	expanded_str = (char **)malloc(sizeof(char *) * (ft_array_len(str) + 1));
	if (!expanded_str)
		return (NULL);
	while (i < ft_array_len(str))
	{
		expanded_str[i] = final_expanded_str(bash, str[i]);
		i++;
	}
	expanded_str[i] = NULL;
	free_array(str);
	return (expanded_str);
}
