/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_modified.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmususa <tmususa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 21:42:07 by yonamog2          #+#    #+#             */
/*   Updated: 2023/09/08 20:17:27 by tmususa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

void	ft_util(unsigned long long res, int sign, t_shell *proc)
{
	(void)proc;
	if (sign == -1)
	{
		if ((res - 1) > LLONG_MAX)
		{
			ft_putstr_fd(": numeric argument required\n", 2);
			garbage_collector(&proc);
			exit(255);
		}
	}
	else
	{
		if (res > LLONG_MAX)
		{
			ft_putstr_fd(": numeric argument required\n", 2);
			garbage_collector(&proc);
			exit(255);
		}
	}
}

void	atoi_utl_with_exit(char *str, int x, t_shell *proc)
{
	while (str[x] && str[x] >= '0' && str[x] <= '9')
	{
		*proc->copy_atoi = *proc->res_atoi;
		*proc->res_atoi = (*proc->res_atoi * 10) + (str[x++] - '0');
		if (*proc->copy_atoi > *proc->res_atoi)
		{
			ft_putstr_fd(": numeric argument required\n", 2);
			garbage_collector(&proc);
			exit(255);
		}
	}
}

int	ft_exit_helper(const char *str, t_shell *proc)
{
	int					x;
	int					sign;
	unsigned long long	res;
	unsigned long long	copy;

	x = 0;
	res = 0;
	sign = 1;
	copy = 0;
	while (str[x] && array_strchr("\t \v\f\n", str[x]))
		x++;
	if (str[x] && (str[x] == '-' || str[x] == '+'))
	{
		if (str[x] == '-')
			sign = -1;
		x++;
	}
	proc->res_atoi = &res;
	proc->copy_atoi = &copy;
	atoi_utl_with_exit((char *)str, x, proc);
	ft_util(res, sign, proc);
	return (res * sign);
}
