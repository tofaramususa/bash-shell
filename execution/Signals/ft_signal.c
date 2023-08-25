/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonamog2 <yonamog2@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:51:00 by yonamog2          #+#    #+#             */
/*   Updated: 2023/02/20 16:47:14 by yonamog2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * sig_handler: a function to handle signal calls
 * @num: number of the signal status
*/
void	sig_handler(int num)
{
	if (num == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		error_status = 1;
	}
}

void	child_signal_handler(int num)
{
	if (num == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		error_status = 130;
	}
	else if (num == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		error_status = 130;
	}
}

void	do_operation(t_shell *proc, t_command *av)
{
	proc->dont = 1;
	if (av->red_len > 0)
		red_one_cmd(av, proc);
}


void init_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

