/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:06:48 by tmususa           #+#    #+#             */
/*   Updated: 2023/09/04 11:03:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

bool	wildcard_match(const char *pattern, const char *d_name, t_quote quotes)
{
	while (*pattern && *d_name)
	{
		set_quote_flag(&quotes, *pattern);
		if (*pattern == '*' && !quotes.single_q && !quotes.double_q)
		{
			pattern++;
			while (*d_name)
			{
				if (wildcard_match(pattern, d_name, quotes))
				{
					return (true);
				}
				d_name++;
			}
			return (*pattern == *d_name);
		}
		else if (*pattern != *d_name)
		{
			return (false);
		}
		pattern++;
		d_name++;
	}
	return (*d_name == *pattern);
}

bool	filename_expansion(t_token **tokenlist, char *str_token)
{
	char			*cwd;
	struct dirent	*entry;
	DIR				*dir;
	bool			match_found;
	char			*expanded_token;
	t_quote			quotes;

	quotes.single_q = false;
	quotes.double_q = false;
	cwd = getcwd(NULL, 0);
	match_found = false;
	dir = opendir(cwd);
	if (!dir)
	{
		perror("opendir");
		if (cwd)
			safe_free(cwd);
		return (match_found);
	}
	if (str_token != NULL && array_strchr(str_token, '*'))
	{
		while ((entry = readdir(dir)) != NULL)
		{
			if (entry->d_name[0] == '.')
			{
				continue ;
			}
			if (wildcard_match(str_token, entry->d_name, quotes))
			{
				expanded_token = ft_strdup(entry->d_name);
				if (expanded_token)
				{
					add_token_node(tokenlist, new_token_node(expanded_token));
					match_found = true;
					free(expanded_token);
				}
			}
		}
	}
	closedir(dir);
	if (cwd)
		safe_free(cwd);
	return (match_found);
}
