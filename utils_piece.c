/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_piece.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:45:31 by glopez-m          #+#    #+#             */
/*   Updated: 2024/02/28 18:39:45 by glopez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_piece	*last_piece(t_piece *piece)
{
	if (!piece)
		return (0);
	while (piece->next)
		piece = piece->next;
	return (piece);
}

int	piecelen(t_piece *list)
{
	int	len;

	len = 0;
	while (list)
	{
		list = list->next;
		len++;
	}
	return (len);
}

void	pieceaddback(t_piece *toadd, t_piece **list)
{
	t_piece	*now;

	if (!*list)
		*list = toadd;
	else
	{
		now = *list;
		while (now->next)
			now = now->next;
		now->next = toadd;
	}
}
