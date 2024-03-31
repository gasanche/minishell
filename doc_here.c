/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc_here.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:45:25 by glopez-m          #+#    #+#             */
/*   Updated: 2024/02/29 12:13:46 by glopez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	write_hd(t_common *common, char *term, int fd, int expands)
{
	char		**expanded;
	char		*line;
	int			len;

	signal(SIGINT, SIG_DFL);
	line = readline("> ");
	while (line)
	{
		if (expands && line[0])
		{
			expanded = expanded_to_array(expandstr(line, common->env,
						common->exstatus, NO_WS));
			free(line);
			line = expanded[0];
			free(expanded);
		}
		len = ft_biggest((int [2]){ft_strlen(line), ft_strlen(term)}, 2);
		if (!ft_strncmp(line, term, len))
			break ;
		if (write(fd, line, ft_strlen(line)) == -1 || write(fd, "\n", 1) == -1)
			pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, 1);
		free(line);
		line = readline("> ");
	}
}

void	_get_hd(t_common *common, const char *name, char *term)
{
	const int	expands = !(ft_strchr(term, '\'') || ft_strchr(term, '\"'));
	int			fd;
	char		*temp;

	fd = open(name, O_WRONLY | O_CREAT | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		pterr((char *[3]){"minishell: ", (char *)name, 0},
			ERR_EXIT | ERR_PROR, 1);
	temp = term;
	term = get_term(term);
	free(temp);
	write_hd(common, term, fd, expands);
	close(fd);
	free((char *) name);
	free(term);
	exit(0);
}

char	*create_hd(char *term, t_common *common)
{
	pid_t		pid;
	int			status;
	const char	*name = findname();

	pid = fork();
	if (pid == -1)
		pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, PERR_PID);
	if (pid == 0)
		_get_hd(common, name, term);
	waitpid(pid, &status, 0);
	if (!WIFEXITED(status))
	{
		g_received = SIGINT;
		common->exstatus = 1;
	}
	return ((char *) name);
}
