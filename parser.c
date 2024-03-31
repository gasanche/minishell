/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:57:42 by glopez-m          #+#    #+#             */
/*   Updated: 2024/03/09 19:03:25 by glopez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_piece	*get_redir(t_piece *redir, t_egg *egg, int offset, t_common *common)
{
	if (redir->flags & (RED_IN_S | RED_IN_D))
		egg->oflags[offset] = O_RDONLY;
	else if (redir->flags & RED_OUT_S)
	{
		egg->oflags[offset] = O_WRONLY | O_CREAT | O_TRUNC;
		egg->optflags[offset] = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	}
	else if (redir->flags & RED_OUT_D)
	{
		egg->oflags[offset] = O_WRONLY | O_CREAT | O_APPEND;
		egg->optflags[offset] = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	}
	if (redir->flags & RED_IN_D)
		return (newpiece(P_UNL | RED_IN_D,
				create_hd(redir->next->chunk, common), 0));
	else
		return (newpiece(redir->flags, ft_strdup(redir->next->chunk), 0));
}

void	get_egg(t_piece *lexed, t_egg *egg, t_common *common)
{
	int			i;
	int			j;

	egg->cmdargv = ft_calloc((countargs(lexed) + 1), sizeof (char *));
	if (!egg->cmdargv)
		pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, ENOMEM);
	i = 0;
	j = 0;
	while (lexed && lexed->flags != '|' && !g_received)
	{
		if (!(lexed->flags & (RED_IN_S | RED_IN_D | RED_OUT_S | RED_OUT_D)))
		{
			egg->cmdargv[i] = ft_strdup(lexed->chunk);
			if (!egg->cmdargv[i++])
				pterr((char *[2]){"minishell: ", 0},
					ERR_EXIT | ERR_PROR, ENOMEM);
		}
		else
		{
			pieceaddback(get_redir(lexed, egg, j++, common), &egg->redirs);
			lexed = lexed->next;
		}
		lexed = lexed->next;
	}
}

void	incubate(t_piece *lexed, t_egg *egg, t_common *common)
{
	const int	argc = countargs(lexed);
	char		**temp;

	get_egg(lexed, egg, common);
	if (egg->cmdargv[0])
	{
		temp = expanded_to_array(expandcmd(egg->cmdargv, argc,
					common->env, common->exstatus));
		if (!temp)
		{
			temp = malloc(sizeof (char *));
			if (!temp)
				pterr((char *[2]){"minishell: ", 0},
					ERR_EXIT | ERR_PROR, ENOMEM);
			temp[0] = 0;
		}
		ft_free_ptr_array((void **) egg->cmdargv, argc, 1);
		egg->cmdargv = temp;
	}
}

t_egg	*parse(t_piece *lexed, t_common *common)
{
	t_egg	*egg_cup;
	int		i;
	t_piece	*now;

	egg_cup = ft_calloc((count_pipes(lexed) + 2), sizeof(t_egg));
	if (!egg_cup)
		pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, ENOMEM);
	i = -1;
	now = lexed;
	while (now)
	{
		egg_cup[++i].oflags = ft_calloc(countredirs(now), sizeof (int));
		if (!egg_cup[i].oflags)
			pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, ENOMEM);
		egg_cup[i].optflags = ft_calloc(countredirs(now), sizeof (int));
		if (!egg_cup[i].oflags)
			pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, ENOMEM);
		incubate(now, &egg_cup[i], common);
		while (now->next && now->flags != '|')
			now = now->next;
		now = now->next;
	}
	egg_cup[0].pos = G_FIRST;
	egg_cup[i + 1].pos = G_LAST;
	return (egg_cup);
}
