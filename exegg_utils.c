/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exegg_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:53:20 by glopez-m          #+#    #+#             */
/*   Updated: 2024/03/03 17:32:52 by glopez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	_set_and_check(char **path, char *toset)
{
	struct stat	data;

	*path = toset;
	if (access(*path, F_OK) == 0)
	{
		stat(*path, &data);
		if (data.st_mode & S_IFDIR)
			pterr((char *[4]){"minishell: ", *path, ": is a directory", 0},
				ERR_EXIT, 126);
	}
	else
		pterr((char *[4]){"minishell: ", *path,
			": No such file or directory", 0}, ERR_EXIT, 127);
}

void	pterr(char **text, char flags, int excode)
{
	int		temp;
	int		i;

	temp = errno;
	i = -1;
	while (text[++i])
		ft_putstr_fd(text[i], 2);
	if (flags & ERR_PROR)
		ft_putstr_fd(strerror(temp), 2);
	write(2, "\n", 1);
	if (flags & ERR_EXIT)
		exit(excode);
}

void	waitall(pid_t *pids, int *status)
{
	int	i;

	i = -1;
	while (pids[++i] != 0)
		waitpid(pids[i], status, 0);
	free(pids);
}

int	retstatus(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
	{
		if (status == 11)
			ft_putstr_fd("Segmentation fault: 11", 2);
		else if (status == 3)
		{
			ft_putstr_fd("Quit: 3", 2);
			g_received = SIGQUIT;
		}
		else if (status == 2)
			g_received = SIGINT;
		write(2, "\n", 1);
		return (128 + status);
	}
}

int	egglen(t_egg *array)
{
	int	i;

	i = 0;
	while (!(array[i].pos & G_LAST))
		i++;
	return (i);
}
