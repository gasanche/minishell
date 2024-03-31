/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 19:35:23 by glopez-m          #+#    #+#             */
/*   Updated: 2024/02/29 15:11:07 by glopez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	delete_piece(t_piece **piece)
{
	free((*piece)->chunk);
	free(*piece);
	*piece = 0;
}

void	scramble_pieces(t_piece **piece)
{
	t_piece	*a;
	t_piece	*b;

	a = *piece;
	b = a;
	while (a)
	{
		b = b->next;
		if (a->flags & P_UNL)
			unlink(a->chunk);
		free(a->chunk);
		free(a);
		a = b;
	}
	*piece = 0;
}

void	break_eggs(t_egg **eggs)
{
	int	i;

	if (!(*eggs))
		return ;
	i = -1;
	while (!((*eggs)[++i].pos & G_LAST))
	{
		scramble_pieces(&((*eggs)[i].redirs));
		free((*eggs)[i].oflags);
		free((*eggs)[i].optflags);
		ft_free_ptr_array((void **)(*eggs)[i].cmdargv,
			ft_arraylen((*eggs)[i].cmdargv), 1);
	}
	free(*eggs);
	*eggs = 0;
}
