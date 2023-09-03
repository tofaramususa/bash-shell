/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:34:02 by tmususa           #+#    #+#             */
/*   Updated: 2023/09/03 19:47:02 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (!check_line(bash->line))
	{
		return (false);
	}
	add_history(bash->line);
	final_result = ft_split_on_delims(bash->line);
	if (!final_result)
	{
		return (false);
	}
	bash->tokenlist = ft_tokenise(bash, final_result);
	if (!bash->tokenlist)
		return (false);
	create_compound_array(bash, bash->tokenlist);
	if (!bash->cmpd_node || !bash->cmpd_node[0])
		return (false);
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
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*bash;

	if (envp[0] == NULL)
		exit(printf("Error: No environment variables found"));
	if (ac > 1 || ft_array_len(av) > 1)
		exit(printf("To start x1b[38;5;122mTheBash\x1b[0m enter: ./minishell"));
	bash = (t_shell *)malloc(sizeof(t_shell));
	if (!bash)
		exit(printf("Memory allocation failure"));
	signal(SIGQUIT, SIG_IGN);
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
		else
			g_error_status = 2;
		parsing_garbage_collector(&bash);
	}
	free_env_list(&bash->env_list);
	free(bash);
}
