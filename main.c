/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 18:09:56 by glopez-m          #+#    #+#             */
/*   Updated: 2024/02/29 15:05:19 by glopez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**replace_env(char	**orig)
{
	char	**ours;
	int		j;

	j = 0;
	ours = malloc(sizeof(char *) * (ft_arraylen(orig) + 2));
	if (!ours)
		pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, ENOMEM);
	while (j < ft_arraylen(orig))
	{
		ours[j] = ft_strdup(orig[j]);
		if (ours[j] == NULL)
			pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, ENOMEM);
		j++;
	}
	ours[j] = NULL;
	return (ours);
}

char	*_readinput(t_common *common)
{
	char		*tmp;
	char		*input;

	g_received = 0;
	signal(SIGINT, ft_sighandler);
	signal(SIGQUIT, SIG_IGN);
	tmp = readline("minishell> ");
	signal(SIGINT, SIG_IGN);
	if (g_received)
		common->exstatus = 1;
	g_received = 0;
	if (!tmp)
		ft_exit(0, common->exstatus);
	input = ft_strtrim(tmp, " \t\n");
	free(tmp);
	return (input);
}

void	_prepare(char **argv, char **env, t_lexer **lexed, t_common *common)
{
	(void)argv;
	using_history();
	*lexed = 0;
	common->env = replace_env(env);
	common->exstatus = 0;
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_lexer		*lexed;
	t_egg		*cmds;
	t_common	common;

	(void)argc;
	_prepare(argv, env, &lexed, &common);
	while (1)
	{
		input = _readinput(&common);
		if (input[0])
		{
			add_history(input);
			if (tokenize(input, &lexed) != -1 && !checktokenerrs(lexed, &common)
				&& !unclosed(input))
			{
				cmds = parse((t_piece *)lexed, &common);
				if (cmds && !g_received)
					common.exstatus = exeggutor(cmds, &common);
				break_eggs(&cmds);
			}
			scramble_pieces((t_piece **) &lexed);
		}
		free(input);
	}
}
