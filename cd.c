/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:50:18 by glopez-m          #+#    #+#             */
/*   Updated: 2024/03/15 14:02:01 by gabsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

/*int	check_env(char **env, char *str)
{
	int	i;

	i = ft_varexists(str, env, explen(str));
	if (i < 0)
		return (0);
	return (1);
}
*/
int	check_env(char **env)
{
	int	pwd;

	pwd = ft_varexists("PWD", env, 3);
	if (pwd < 0)
		return (-1);
	return (pwd);
}

void	ft_oldpwd(char ***env, char **oldpwd, char **joined, int var_s)
{
	oldpwd[0] = ft_substr(env[0][var_s], 4, ft_strlen(env[0][var_s] + 4));
	if (!oldpwd && !oldpwd[0])
		pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, ENOMEM);
	joined[0] = ft_strjoin("OLDPWD=", oldpwd[0]);
	if (!joined[0])
		pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, ENOMEM);
	env[0] = new_exp(joined[0], env[0], 1);
}

char	**change_pwd(char **env)
{
	char	*oldpwd;
	char	*pwd;
	char	*joined;
	int		var_s;

	var_s = check_env(env);
	oldpwd = NULL;
	if (var_s != -1)
	{
		ft_oldpwd(&env, &oldpwd, &joined, var_s);
		free(joined);
	}
	if (var_s == -1 && ft_varexists("OLDPWD", env, 6) > -1)
		env = new_exp("OLDPWD=", env, 1);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, ENOMEM);
	joined = ft_strjoin("PWD=", pwd);
	if (!joined)
		pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, ENOMEM);
	env = new_exp(joined, env, 1);
	return (free(oldpwd), free(pwd), free(joined), env);
}

char	*ft_home(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

int	cd(t_egg *info, char ***env)
{
	int	i;

	i = 0;
	if (!info->cmdargv[1]
		|| (info->cmdargv[1][0] == '~' && !info->cmdargv[1][1]))
	{
		i = chdir(ft_home(env[0]));
		if (i == -1)
			pterr((char *[4]){"minishell: cd: ", info->cmdargv[1], ": ", 0},
				ERR_PROR, 0);
	}
	else if (!info->cmdargv[1][0])
		return (0);
	else if (chdir(info->cmdargv[1]) == -1)
	{
		pterr((char *[4]){"minishell: cd: ", info->cmdargv[1], ": ", 0},
			ERR_PROR, 0);
		return (1);
	}
	env[0] = change_pwd(env[0]);
	return (0);
}
