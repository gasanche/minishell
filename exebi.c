/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exebi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 17:05:38 by glopez-m          #+#    #+#             */
/*   Updated: 2024/03/16 17:34:23 by gabsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	exebi(t_egg *info, t_common *common)
{
	if (!ft_strncmp(info->cmdargv[0], "echo", 4))
		return (echo(info));
	else if (!ft_strncmp(info->cmdargv[0], "cd", 2))
		return (cd(info, &(common->env)));
	else if (!ft_strncmp(info->cmdargv[0], "pwd", 3))
		return (pwd());
	else if (!ft_strncmp(info->cmdargv[0], "export", 6))
		return (ft_export(info, &(common->env), &(common->exstatus)));
	else if (!ft_strncmp(info->cmdargv[0], "unset", 5))
		return (unset(info, common->env, &(common->exstatus)));
	else if (!ft_strncmp(info->cmdargv[0], "env", 3))
		return (env(common->env));
	else if (!ft_strncmp(info->cmdargv[0], "exit", 4))
		return (ft_exit(info, common->exstatus));
	return (1);
}
