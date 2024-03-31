/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:53:14 by glopez-m          #+#    #+#             */
/*   Updated: 2024/02/24 16:55:08 by glopez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	countargs(t_piece *lexed)
{
	int			amt;
	const int	isred = RED_IN_S | RED_IN_D | RED_OUT_S | RED_OUT_D;

	amt = 0;
	while (lexed && lexed->flags != '|')
	{
		if (!(lexed->flags & isred))
			amt++;
		else
			lexed = lexed->next;
		lexed = lexed->next;
	}
	return (amt);
}

int	countredirs(t_piece	*lexed)
{
	int			amt;
	const int	isred = RED_IN_S | RED_IN_D | RED_OUT_S | RED_OUT_D;

	amt = 0;
	while (lexed && lexed->flags != '|')
	{
		if (lexed->flags & isred)
			amt++;
		lexed = lexed->next;
	}
	return (amt);
}

int	count_pipes(t_piece *list)
{
	int	count;

	count = 0;
	while (list)
	{
		if (list->flags == '|')
			count++;
		list = list->next;
	}
	return (count);
}
