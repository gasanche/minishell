/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:52:22 by glopez-m          #+#    #+#             */
/*   Updated: 2024/03/03 15:31:04 by gabsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	ft_isstrnum(char *str)
{
	int		i;
	char	c;

	i = 0;
	if (str[0] == '-')
		i++;
	if (!str[i])
		return (0);
	c = str[i];
	while (('0' <= c && c <= '9'))
		c = str[++i];
	if (!c)
		return (1);
	return (0);
}

int	ft_exit(t_egg *info, int exstatus)
{
	ft_putstr_fd("exit\n", 2);
	if (!info || !info->cmdargv[1])
		exit(exstatus);
	else if (!ft_isstrnum(info->cmdargv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(info->cmdargv[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("numeric argument required\n", 2);
		exit(255);
	}
	else if (info->cmdargv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	else
		exit(ft_atoi(info->cmdargv[1]));
	return (1);
}
