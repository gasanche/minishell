/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabsanch <gabsanch@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:00:32 by gabsanch          #+#    #+#             */
/*   Updated: 2024/03/15 12:08:11 by gabsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(char **env)
{
	int	i;

	i = 0;
	if (env && env[i])
	{
		while (env[i])
		{
			free(env[i]);
			i++;
		}
		free(env);
	}
}

char	*ft_getvar_exp(char *str, int i)
{
	char	*tmp;

	tmp = ft_substr(str, 0, i);
	if (!tmp)
		pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, ENOMEM);
	return (tmp);
}

int	ft_varexists(char *str, char **env, int k)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (env && env[i] && ft_strncmp(str, env[i], k) == 0
			&& env[i][k] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	var_replace(char *str, char **env, int i)
{
	char	*tmp;

	tmp = env[i];
	env[i] = ft_strdup(str);
	if (!env[i])
		pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, ENOMEM);
	free(tmp);
}
