/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:42:18 by yonamog2          #+#    #+#             */
/*   Updated: 2023/09/08 22:27:24 by marvin           ###   ########.fr       */
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

void	replace_heredocs_helper(t_redir *redir, t_shell *bash,
		t_heredoc_var *var)
{
	char	*temp_str;

	temp_str = remove_quotes(redir->filename, 0);
	if (!array_strchr(redir->filename, '"') && !array_strchr(redir->filename,
			'\'') && !array_strchr(redir->filename, '$'))
	{
		var->tmp = final_expanded_str(bash, var->tmp);
	}
	var->delimiter = ft_strjoin(temp_str, "\n");
	var->ret = replace_heredocs_util(redir, var);
	safe_free(temp_str);
	temp_str = NULL;
}

/**
 * replace_heredocs: replace the << with tmp file
 * @av:
 * @proc:
 */
int	replace_heredocs(t_redir *redir, t_shell *bash)
{
	t_heredoc_var	var;

	var.ret = 0;
	var.delimiter = NULL;
	var.file1 = open(".tmp", O_RDWR | O_CREAT | O_APPEND | O_TRUNC, 0777);
	if (var.file1 == -1)
		terminate(redir->filename, bash);
	while (1)
	{
		signal(SIGINT, SIG_IGN);
		var.tmp = get_next_line(0);
		if (var.tmp == NULL)
			return (close(var.file1), 1);
		replace_heredocs_helper(redir, bash, &var);
		if (var.ret == 1)
			return (1);
		if (var.ret == 2)
			break ;
		safe_free(var.delimiter);
		write(var.file1, var.tmp, ft_strlen(var.tmp));
		safe_free(var.tmp);
	}
	return (0);
}

/**
 * check_and_update_heredoc: check if there is heredoc and accept input
 * @av:
 * @proc:
 */
int	check_and_update_heredoc(t_compound *cpmd_node, t_shell *bash)
{
	int		index;
	t_redir	*temp;

	index = 0;
	while (index < cpmd_node->cmd_len)
	{
		temp = cpmd_node->s_commands[index]->redirs;
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
