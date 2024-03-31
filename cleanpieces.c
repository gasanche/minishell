/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanpieces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:19:44 by glopez-m          #+#    #+#             */
/*   Updated: 2024/02/28 20:27:59 by glopez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static int	_isnothing(t_piece *list)
{
	while (list)
	{
		if (list->chunk[0] || list->flags & (P_SQT | P_DQT))
			return (0);
		list = list->next;
	}
	return (1);
}

void	_match_pieces(t_piece *now)
{
	t_piece	*trash;
	char	*temp;

	temp = ft_strjoin(now->chunk, now->next->chunk);
	if (!temp)
		pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, ENOMEM);
	free(now->chunk);
	now->chunk = temp;
	trash = now->next;
	now->next = now->next->next;
	delete_piece(&trash);
}

t_piece	*cleanpieces(t_piece **list)
{
	t_piece	*now;

	now = *list;
	if (((*list)->next) && _isnothing((*list)->next))
		scramble_pieces(list);
	else if ((*list)->next)
	{
		(*list)->flags = (*list)->next->flags;
		while (now->next)
		{
			if (!(now->next->flags & P_SLT))
				_match_pieces(now);
			else
				now = now->next;
		}
	}
	return (*list);
}
