/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 21:53:21 by glopez-m          #+#    #+#             */
/*   Updated: 2024/02/29 11:12:13 by glopez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_piece	*newpiece(int status, char *chunk, t_piece *next)
{
	t_piece	*created;

	if (!chunk)
		pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, ENOMEM);
	created = malloc(sizeof(t_piece));
	if (!created)
		pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, ENOMEM);
	created->flags = status | P_MLC;
	created->chunk = chunk;
	if (!created->chunk)
		created->flags = status & (~P_MLC);
	created->next = next;
	return (created);
}
