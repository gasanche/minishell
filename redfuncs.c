/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redfuncs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 21:07:01 by glopez-m          #+#    #+#             */
/*   Updated: 2024/03/16 19:08:18 by glopez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	savestd(int	*std)
{
	std[0] = dup(STDIN_FILENO);
	if (std[0] == -1)
		pterr((char *[2]){"minishell: savestd:", 0}, ERR_EXIT | ERR_PROR, 1);
	std[1] = dup(STDOUT_FILENO);
	if (std[1] == -1)
		pterr((char *[2]){"minishell: savestd:", 0}, ERR_EXIT | ERR_PROR, 1);
}

void	redstd(int *fds)
{
	int	returns[2];

	returns[0] = dup2(fds[0], STDIN_FILENO);
	if (returns[0] == -1)
		pterr((char *[2]){"minishell: redstd:", 0}, ERR_EXIT | ERR_PROR, 1);
	if (fds[0] != STDIN_FILENO)
		close(fds[0]);
	returns[1] = dup2(fds[1], STDOUT_FILENO);
	if (returns[1] == -1)
		pterr((char *[2]){"minishell: redstd:", 0}, ERR_EXIT | ERR_PROR, 1);
	if (fds[1] != STDOUT_FILENO)
		close(fds[1]);
}

int	get_file(t_piece *file, int oflags, int optflags, t_common *common)
{
	int		fd;
	t_piece	*expanded;

	expanded = expandstr(file->chunk, common->env, common->exstatus, 0);
	if (!expanded || (!expanded->chunk[0] && (expanded->flags & P_EXP))
		|| expanded->next)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file->chunk, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		scramble_pieces(&expanded);
		return (-1);
	}
	fd = open(expanded->chunk, oflags, optflags);
	if (fd == -1)
		pterr((char *[4]){"minishell: ", expanded->chunk, ": ", 0},
			ERR_PROR, 0);
	scramble_pieces(&expanded);
	return (fd);
}

int	redirects(int fds[2], t_egg *info, t_common *common)
{
	int		i;
	int		pipe_end;
	t_piece	*now;

	i = 0;
	now = info->redirs;
	while (now)
	{
		if (now->flags & (RED_IN_S | RED_IN_D))
			pipe_end = 0;
		else
			pipe_end = 1;
		close(fds[pipe_end]);
		fds[pipe_end] = get_file(now, info->oflags[i],
				info->optflags[i], common);
		if (fds[pipe_end] == -1)
		{
			close(fds[!pipe_end]);
			return (0);
		}
		now = now->next;
		i++;
	}
	redstd(fds);
	return (1);
}
