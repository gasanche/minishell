/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:17:24 by glopez-m          #+#    #+#             */
/*   Updated: 2024/03/16 17:40:36 by gabsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

char	*ft_addargv(char *str, int type)
{
	char	*var;
	char	*tmp;
	int		i;

	i = 0;
	while (str[i] != '=' && str[i] != '+')
		i++;
	var = ft_substr(str, 0, i);
	tmp = var;
	if (var == NULL)
		pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, ENOMEM);
	if (type == 0)
		var = ft_strjoin(var, str + i + 1);
	else if (type == 1)
		var = ft_strjoin(var, str + i);
	free(tmp);
	return (var);
}

char	**new_exp(char *str, char **env, int type)
{
	int			j;
	char		**tmp_env;

	if (ft_varexists(str, env, explen(str)) != -1 && type != 0)
	{
		var_replace(str, env, ft_varexists(str, env, explen(str)));
		return (env);
	}
	else
	{
		j = -1;
		tmp_env = malloc(sizeof (char *) * (ft_arraylen(env) + 2));
		if (!tmp_env)
			pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, ENOMEM);
		while (++j < ft_arraylen(env))
		{
			tmp_env[j] = ft_strdup(env[j]);
			if (tmp_env[j] == NULL)
				return (NULL);
		}
		tmp_env[j] = ft_addargv(str, type);
		tmp_env[j + 1] = NULL;
		free_env(env);
	}
	return (tmp_env);
}

char	**app_exp(char *str, char **env, int k)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strncmp(str, env[i], k) == 0 && env[i][k] == '=')
		{
			var_append(str + k + 2, env, i);
			return (env);
		}
		i++;
	}
	return (new_exp(str, env, 0));
}

char	**der_ft(t_egg *info, int i, int j, char ***envp)
{
	if (info->cmdargv[i][j] == '+' && info->cmdargv[i][j + 1] == '=')
		return (app_exp(info->cmdargv[i], *envp, j));
	else if (info->cmdargv[i][j] == '=')
		return (new_exp(info->cmdargv[i], *envp, 1));
	return (NULL);
}

int	ft_export(t_egg *info, char ***envp, int *exstt)
{
	char	**tmp_env;
	int		i;
	int		j;
	int		flag;

	if (!info->cmdargv[1])
		print_vars(*envp);
	else
	{
		i = 0;
		while (info->cmdargv[++i])
		{
			flag = 0;
			j = ft_var_is_valid(info->cmdargv[i], 1);
			if (j && ft_isexport(info->cmdargv[i][j]))
				tmp_env = der_ft(info, i, j, envp);
			else if (j && info->cmdargv[i][j] == '\0')
				continue ;
			else
				flag = ft_print_not_valid(info->cmdargv[i], exstt);
			if (flag == 0)
				*envp = tmp_env;
		}
	}
	return (*exstt);
}
