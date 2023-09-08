/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:06:48 by tmususa           #+#    #+#             */
/*   Updated: 2023/09/08 20:17:03 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static bool	wildcard_match(const char *pattern, const char *d_name,
		t_quote quotes)
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

static bool	add_wildcard_tokens(DIR *dir, char *str_token, t_token **tokenlist,
		char *expanded_token)
{
	t_quote			quotes;
	struct dirent	*entry;
	bool			match_found;

	match_found = false;
	quotes.single_q = false;
	quotes.double_q = false;
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (entry->d_name[0] != '.' && wildcard_match(str_token, entry->d_name,
				quotes))
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
	return (match_found);
}

bool	filename_expansion(t_token **tokenlist, char *str_token)
{
	char	*cwd;
	DIR		*dir;
	bool	match_found;
	char	*expanded_token;

	expanded_token = NULL;
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
		match_found = add_wildcard_tokens(dir, str_token, tokenlist,
				expanded_token);
	}
	closedir(dir);
	if (cwd)
		safe_free(cwd);
	return (match_found);
}
