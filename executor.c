/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:17:40 by glopez-m          #+#    #+#             */
/*   Updated: 2024/03/09 19:02:53 by glopez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	breed_process(int fds[2], t_egg *info, t_common *common)
{
	char		*path;
	const char	*bins[] = {"echo", "cd", "pwd", "export", "unset", "env",
		"exit", 0};

	if (!redirects(fds, info, common))
		exit(1);
	if (!info->cmdargv || !info->cmdargv[0])
		exit(0);
	if (ft_strchr(info->cmdargv[0], '/'))
		_set_and_check(&path, info->cmdargv[0]);
	else if (isstrin(info->cmdargv[0], bins))
		exit(exebi(info, common));
	else
		path = get_function(info->cmdargv[0], common->env);
	if (!path)
		_set_and_check(&path, info->cmdargv[0]);
	if (!info->cmdargv[0][0] || access(path, F_OK) != 0)
		pterr((char *[4]){"minishell: ", info->cmdargv[0],
			": command not found", 0}, ERR_EXIT, 127);
	if (execve(path, info->cmdargv, common->env) == -1)
		pterr((char *[4]){"minishell: ", info->cmdargv[0], ": ", 0},
			ERR_EXIT | ERR_PROR, 126);
}

void	preprocess(t_egg *info, t_common *common, int fds[2])
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!(info[1].pos & G_LAST))
		breed_process(fds, info, common);
	else
	{
		close(fds[1]);
		if (info->pos & G_FIRST)
			breed_process((int [2]){STDIN_FILENO, STDOUT_FILENO},
				info, common);
		else
			breed_process((int [2]){fds[0], STDOUT_FILENO}, info, common);
	}
}

static void	loop(pid_t *pids, t_egg *info, t_common *common)
{
	int	i;
	int	temp;
	int	fds[2];

	temp = STDIN_FILENO;
	i = -1;
	while (!(info[++i].pos & G_LAST))
	{
		if (pipe(fds) == -1)
			pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, PERR_PPE);
		pids[i] = fork();
		if (pids[i] == -1)
			pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, PERR_PID);
		if (!pids[i])
		{
			close(fds[0]);
			preprocess(&info[i], common, (int [2]){temp, fds[1]});
		}
		close(fds[1]);
		if (temp != STDIN_FILENO)
			close(temp);
		temp = fds[0];
	}
	if (temp != STDIN_FILENO)
		close(temp);
}

int	general_case(t_egg *info, t_common *common)
{
	pid_t		*pids;
	const int	processes = egglen(info);

	pids = malloc((processes + 1) * sizeof (pid_t));
	if (!pids)
		pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, ENOMEM);
	pids[processes] = 0;
	loop(pids, info, common);
	waitall(pids, &(common->exstatus));
	return (retstatus(common->exstatus));
}

int	exeggutor(t_egg *info, t_common *common)
{
	const char	*bins[] = {"echo", "cd", "pwd", "export", "unset", "env",
		"exit", 0};
	int			std[2];
	int			ret;

	if (isstrin(info[0].cmdargv[0], bins) && (info[1].pos & G_LAST))
	{
		savestd(std);
		if (redirects((int [2]){STDIN_FILENO, STDOUT_FILENO}, info, common))
			ret = exebi(info, common);
		else
			ret = 1;
		redstd(std);
		return (ret);
	}
	else
		return (general_case(info, common));
}
