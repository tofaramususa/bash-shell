/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_methods.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:57:48 by tmususa           #+#    #+#             */
/*   Updated: 2023/09/10 16:36:04 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	free_short(char *path, char **path_split)
{
	safe_free(path);
	free_array(path_split);
}

void	collect_and_exit(t_shell *bash, char *message)
{
	garbage_collector(&bash);
	exit(printf("%s\n", message));
}

void	free_token_list(t_token **tokenlist)
{
	t_token	*next_node;
	t_token	*current;

	current = *tokenlist;
	if (current)
	{
		while (current)
		{
			next_node = current->next;
			if (current && current->isfreed == false)
			{
				current->isfreed = true;
				free(current->value);
				free(current);
			}
			current = next_node;
		}
		*tokenlist = NULL;
	}
}

void	get_display_line(t_shell *bash, char **prompt)
{
	char	*temp_str;

	temp_str = NULL;
	if (g_error_status == 0)
	{
		temp_str = ft_strjoin("\x1b[38;5;190m 🏀", getcwd(bash->pwd, 1024));
		if (temp_str)
			*prompt = ft_strjoin(temp_str, "\x1b[38;5;122m [THEBASH]$ \x1b[0m");
		else
			*prompt = ft_strjoin("\x1b[38;5;190m 🏀",
					"\x1b[38;5;122m [THEBASH]$ \x1b[0m");
	}
	else
	{
		temp_str = ft_strjoin("\x1b[38;5;190m 🗑️ ", getcwd(bash->pwd, 1024));
		if (temp_str)
			*prompt = ft_strjoin(temp_str, "\x1b[38;5;122m [THEBASH]$ \x1b[0m");
		else
			*prompt = ft_strjoin("\x1b[38;5;190m 🗑️ ",
					"\x1b[38;5;122m [THEBASH]$ \x1b[0m");
	}
	if (temp_str)
		safe_free(temp_str);
}
