/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:34:14 by tmususa           #+#    #+#             */
/*   Updated: 2023/09/05 17:35:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

bool	start_execution(t_compound *cpmd_node, t_shell *bash)
{
	if (cpmd_node->cmd_len >= 220)
	{
		ft_putstr_fd("Sorry too many commands\n", 2);
		g_error_status = 1;
		return (false);
	}
	if (check_and_update_heredoc(cpmd_node->s_commands, bash) == 1)
	{
		garbage_collector(&bash);
		exit(1);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, sig_handler);
	g_error_status = pipex(cpmd_node->cmd_len, cpmd_node->s_commands, bash);
	unlink(".tmp");
	return (false);
}

bool	should_execute(t_compound *node)
{
	if (node->split_on == AND && g_error_status != 0)
		return (false);
	else if (node->split_on == OR && g_error_status == 0)
		return (false);
	else
		return (true);
	return (true);
}

int	process_parens(t_compound **nodes, int start, t_shell *bash)
{
	int	end;

	end = start;
	bash->counter = 0;
	while (nodes[end])
	{
		if (nodes[end]->paren == AFTER_OPEN_PAREN && bash->counter == 0)
			start_execution(nodes[end], bash);
		else if (nodes[end]->paren == AFTER_OPEN_PAREN)
		{
			end = process_parens(nodes, end, bash);
			continue ;
		}
		else
		{
			if (should_execute(nodes[end]))
				start_execution(nodes[end], bash);
			if (nodes[end]->paren == BEFORE_CLOSE_PAREN)
			{
				end++;
				break ;
			}
		}
		end++;
		bash->counter++;
	}
	return (end);
}

void	line_prompt(t_shell *bash)
{
	char	*temp_str;
	char	*prompt;

	prompt = NULL;
	temp_str = NULL;
	if (g_error_status == 0)
	{
		temp_str = ft_strjoin("\x1b[38;5;190m 🏀", getcwd(bash->pwd, 1024));
		prompt = ft_strjoin(temp_str, "\x1b[38;5;122m [THEBASH]$ \x1b[0m");
		bash->line = readline(prompt);
	}
	else
	{
		temp_str = ft_strjoin("\x1b[38;5;190m 🗑️ ", getcwd(bash->pwd, 1024));
		prompt = ft_strjoin(temp_str, "\x1b[38;5;122m [THEBASH]$ \x1b[0m");
		bash->line = readline(prompt);
	}
	if (prompt)
		safe_free(prompt);
	if (temp_str)
		safe_free(temp_str);
	if (bash->line == NULL)
	{
		exit(g_error_status);
	}
}

void	parsing_garbage_collector(t_shell **bash)
{
	if (bash && *bash)
	{
		if ((*bash)->isfreed == false)
		{
			(*bash)->isfreed = true;
			if ((*bash)->env_vars)
				free_t_char(&((*bash)->env_vars));
			if ((*bash)->line)
				safe_free((*bash)->line);
			if ((*bash)->cmpd_node)
				free_compoundlist(&((*bash)->cmpd_node));
			if ((*bash)->tokenlist)
				free_token_list(&((*bash)->tokenlist));
		}
	}
}