/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:38:10 by glopez-m          #+#    #+#             */
/*   Updated: 2024/03/16 17:54:24 by glopez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	ft_unset_not_valid(char *var, int *exstt)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	*exstt = 1;
	return (1);
}

int	unset_env(char ***env, int i)
{
	free(env[0][i]);
	while (env[0][i + 1])
	{
		env[0][i] = env[0][i + 1];
		i++;
	}
	env[0][i] = NULL;
	return (i);
}

int	unset(t_egg *info, char **env, int *exstt)
{
	int	i;
	int	j;
	int	k;

	j = 0;
	if (!info->cmdargv[1])
		return (-1);
	while (info->cmdargv[++j])
	{
		i = -1;
		if (!ft_var_is_valid(info->cmdargv[j], 1))
			ft_unset_not_valid(info->cmdargv[j], exstt);
		while (env[++i])
		{
			k = ft_strlen(info->cmdargv[j]);
			if (ft_strncmp(env[i], info->cmdargv[j], k) == 0
				&& env[i][k] == '=')
				i = unset_env(&env, i);
			if (!env[i])
				break ;
		}
	}
	return (*exstt);
}
