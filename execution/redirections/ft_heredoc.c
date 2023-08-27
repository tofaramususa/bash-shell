/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:42:18 by yonamog2          #+#    #+#             */
/*   Updated: 2023/08/27 15:49:14 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * replace_heredocs_util: main loop to replace the << with tmp file
 * @av:
 * @proc:
 */
int	replace_heredocs_util(t_command *av, t_redir *redir, t_heredoc_var *var)
{
	if (var->tmp == NULL)
	{
		safefree(var->delimiter);
		error_status = 0;
		close(var->file1);
		return (1);
	}
	else if (ft_strcmp(var->tmp, var->delimiter) == 0)
	{
		safefree(var->delimiter);            // free string
		safefree(redir->filename);           // free string which is a filename
		redir->filename = ft_strdup(".tmp"); // give it a new name
		redir->type = INPUT;                 // change it to a input sign
		close(var->file1);
		safefree(var->tmp);
		return (2);
	}
	return (0);
}

/**
 * replace_heredocs: replace the << with tmp file
 * @av:
 * @proc:
 */
int	replace_heredocs(t_command *s_commands, t_redir *redir, t_shell *bash)
{
	t_heredoc_var	var;

	var.file1 = open(".tmp", O_RDWR | O_CREAT | O_APPEND | O_TRUNC, 0777);
	if (var.file1 == -1)
		terminate(redir->filename, bash, s_commands);
	while (1)
	{
		signal(SIGINT, SIG_IGN);
		var.tmp = get_next_line(0);
		if (var.tmp == NULL)
			return (close(var.file1), 1);
		if (!array_strchr(redir->filename, '"')
				|| !array_strchr(redir->filename, '\'')) // means in quotes
		{
			var.tmp = final_expanded_str(bash, var.tmp);
		}
		else
			redir->filename = remove_quotes(redir->filename);
		var.delimiter = ft_strjoin(redir->filename, "\n");
			// we assign the delimiter name to delimiter
		var.ret = replace_heredocs_util(s_commands, redir, &var);
		if (var.ret == 1)
			return (1);
		if (var.ret == 2)
			break ;
		safefree(var.delimiter);
		write(var.file1, var.tmp, ft_strlen(var.tmp));
			// write the line to file1
		safefree(var.tmp);
	}
	return (0);
}

/**
 * check_and_update_heredoc: check if there is heredoc and accept input
 * @av:
 * @proc:
 */
int	check_and_update_heredoc(t_command *s_commands, t_shell *bash)
{
	int		index;
	int		y;
	t_redir	*temp;

	index = 0;
	while (index < bash->total_scommands) // for every command
	{
		temp = s_commands[index].redirs;
		while (temp) // for every redirection
		{
			if (temp->type == HEREDOC)                            
				// if the sign is a heredoc
				if (replace_heredocs(s_commands, temp, bash) == 1)
					// then we create
					return (1);
			temp = temp->next;
		}
		index++;
	}
	return (0);
}
