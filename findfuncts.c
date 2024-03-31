/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findfuncts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:14:37 by glopez-m          #+#    #+#             */
/*   Updated: 2024/03/01 12:25:10 by gabsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	ft_namelen(char *name)
{
	int	i;

	i = 0;
	while (name[i] && name[i] != '=')
		i++;
	return (i);
}

char	*ft_getenv(char **env, char *var)
{
	const int	len = ft_strlen(var);
	int			i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], var,
			ft_biggest((int [2]){len, ft_namelen(env[i])}, 2)))
		i++;
	if (!env[i] || env[i][len + 1] == '\0')
		return (0);
	return (ft_strdup(&env[i][len + 1]));
}

static char	*buildpath(char *route, char *command)
{
	char	*res;
	int		i;
	int		j;

	res = malloc((ft_strlen(route) + ft_strlen(command) + 2) * sizeof (char));
	if (!res)
		pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, ENOMEM);
	i = -1;
	while (route[++i])
		res[i] = route[i];
	res[i] = '/';
	j = -1;
	while (command[++j])
		res[++i] = command[j];
	res[++i] = '\0';
	return (res);
}

char	**get_paths(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH",
			ft_biggest((int [2]){4, ft_namelen(env[i])}, 2)))
		i++;
	if (!env[i])
		return (0);
	paths = ft_split(&(env[i][5]), ':');
	if (!paths)
		pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, ENOMEM);
	return (paths);
}

char	*get_function(char *fname, char **envp)
{
	char	**path;
	char	*temp;
	int		i;

	path = get_paths(envp);
	if (!path)
		return (0);
	i = -1;
	while (path[++i])
	{
		temp = buildpath(path[i], fname);
		if (!access(temp, F_OK))
			break ;
		else if (!path[i + 1])
			pterr((char *[4]){"minishell: ", fname, ": command not found", 0},
				ERR_EXIT, 127);
		else
			free(temp);
	}
	return (temp);
}
