/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lxr_lstnew.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabsanch <gabsanch@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:59:46 by gabsanch          #+#    #+#             */
/*   Updated: 2024/02/26 14:24:09 by gabsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	istoken(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

t_lexer	*ft_lxr_last(t_lexer *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (!(lst->next))
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lxr_addback(t_lexer **lst, t_lexer *new)
{
	t_lexer	*temp;

	if (lst)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			temp = ft_lxr_last(*lst);
			temp->next = new;
		}
	}
}
