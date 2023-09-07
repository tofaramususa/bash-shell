/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:42:18 by yonamog2          #+#    #+#             */
/*   Updated: 2023/09/06 17:44:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/**
 * replace_heredocs_util: main loop to replace the << with tmp file
 * @av:
 * @proc:
 */
int	replace_heredocs_util(t_redir *redir, t_heredoc_var *var)
{
	if (var->tmp == NULL)
	{
		safe_free(var->delimiter);
		g_error_status = 0;
		close(var->file1);
		return (1);
	}
	else if (ft_strcmp(var->tmp, var->delimiter) == 0)
	{
		safe_free(var->delimiter);
		safe_free(redir->filename);
		redir->filename = ft_strdup(".tmp");
		redir->type = INPUT;
		close(var->file1);
		safe_free(var->tmp);
		return (2);
	}
	return (0);
}

/**
 * replace_heredocs: replace the << with tmp file
 * @av:
 * @proc:
 */
int	replace_heredocs(t_redir *redir, t_shell *bash)
{
	t_heredoc_var	var;
	char *temp_str;

	var.file1 = open(".tmp", O_RDWR | O_CREAT | O_APPEND | O_TRUNC, 0777);
	if (var.file1 == -1)
		terminate(redir->filename, bash);
	temp_str = ft_strdup(redir->filename);
	while (1)
	{
		signal(SIGINT, SIG_IGN);
		var.tmp = get_next_line(0);
		if (var.tmp == NULL)
			return (close(var.file1), 1);
		if (!array_strchr(temp_str, '"')
				&& !array_strchr(temp_str, '\'') && !array_strchr(temp_str, '$'))
		{
			var.tmp = final_expanded_str(bash, var.tmp);
		}
		redir->filename = remove_quotes(redir->filename);
		var.delimiter = ft_strjoin(redir->filename, "\n");
		var.ret = replace_heredocs_util(redir, &var);
		if (var.ret == 1)
			return (1);
		if (var.ret == 2)
			break ;
		safe_free(var.delimiter);
		write(var.file1, var.tmp, ft_strlen(var.tmp));
		safe_free(var.tmp);
	}
	safe_free(temp_str);
	return (0);
}

/**
 * check_and_update_heredoc: check if there is heredoc and accept input
 * @av:
 * @proc:
 */
int	check_and_update_heredoc(t_command **s_commands, t_shell *bash)
{
	int		index;
	t_redir	*temp;

	index = 0;
	while (index < bash->cmd_len)
	{
		temp = s_commands[index]->redirs;
		while (temp != NULL)
		{
			if (temp->type == HEREDOC)
			{
				if (replace_heredocs(temp, bash) == 1)
					return (1);
			}
			temp = temp->next;
		}
		index++;
	}
	return (0);
}
