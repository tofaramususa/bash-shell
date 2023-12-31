/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:34:14 by tmususa           #+#    #+#             */
/*   Updated: 2023/09/10 16:50:17 by tmususa          ###   ########.fr       */
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
	if (check_and_update_heredoc(cpmd_node, bash) == 1)
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
		else if (nodes[end]->paren != AFTER_OPEN_PAREN)
		{
			if (should_execute(nodes[end]))
				start_execution(nodes[end], bash);
			if (nodes[end]->paren == BEFORE_CLOSE_PAREN)
			{
				end++;
				break ;
			}
		}
		else
			end = process_parens(nodes, end, bash);
		end++;
		bash->counter++;
	}
	return (end);
}

void	line_prompt(t_shell *bash)
{
	char	*prompt;

	prompt = NULL;
	get_display_line(bash, &prompt);
	bash->line = readline(prompt);
	if (prompt)
		safe_free(prompt);
	if (!bash->line)
		collect_and_exit(bash, "\nExiting....\n");
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
