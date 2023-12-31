/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:34:02 by tmususa           #+#    #+#             */
/*   Updated: 2023/09/09 22:11:21 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int		g_error_status = 0;

void	execute(t_shell *bash)
{
	int	i;

	i = 0;
	while (bash && bash->cmpd_node && bash->cmpd_node[i])
	{
		if (bash->cmpd_node[i]->paren == AFTER_OPEN_PAREN)
		{
			i = process_parens(bash->cmpd_node, i, bash);
			continue ;
		}
		else if (i == 0)
			start_execution(bash->cmpd_node[i], bash);
		else if (should_execute(bash->cmpd_node[i]))
			start_execution(bash->cmpd_node[i], bash);
		i++;
	}
}

bool	parse(t_shell *bash)
{
	char	**final_result;
	bool	syntax;

	if (!check_line(bash->line))
	{
		return (g_error_status = 0, false);
	}
	add_history(bash->line);
	final_result = ft_split_on_delims(bash->line);
	syntax = ft_tokenise(bash, final_result);
	if (syntax == false)
	{
		if (!bash->tokenlist)
			g_error_status = 0;
		else
			g_error_status = 258;
		return (false);
	}
	create_compound_array(bash, bash->tokenlist);
	if (!bash->cmpd_node)
		return (free_token_list(&bash->tokenlist), false);
	free_token_list(&bash->tokenlist);
	return (true);
}

void	init_bash(t_shell *bash)
{
	bash->dont = 0;
	bash->cmpd_node = NULL;
	bash->env_vars = NULL;
	bash->temp_list = NULL;
	bash->line = NULL;
	bash->tokenlist = NULL;
	bash->isfreed = false;
	bash->result = NULL;
	bash->split_on = PIPE;
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*bash;

	signal(SIGQUIT, SIG_IGN);
	if (!envp || envp[0] == NULL)
		exit(printf("Error: No environment variables found\n"));
	if (ac > 1 || ft_array_len(av) > 1)
		exit(printf("To start x1b[38;5;122mTheBash\x1b[0m enter: ./minishell\n"));
	bash = (t_shell *)malloc(sizeof(t_shell));
	if (!bash)
		exit(printf("Memory allocation failure\n"));
	create_envlist(bash, envp);
	while (1)
	{
		init_bash(bash);
		init_signals();
		line_prompt(bash);
		if (parse(bash))
		{
			execute(bash);
		}
		parsing_garbage_collector(&bash);
	}
	free_env_list(&bash->env_list);
	free(bash);
}
