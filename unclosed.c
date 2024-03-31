/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:48:01 by glopez-m          #+#    #+#             */
/*   Updated: 2024/02/25 20:12:36 by glopez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

//Returns 0 when there are no unclosed quotes and 1 when there are
int	unclosed(char *str)
{
	int	i;

	i = 0;
	while (1)
	{
		while (str[i] && str[i] != '\'' && str[i] != '\"')
			i++;
		if (!str[i])
			return (0);
		i += skip_until_next(&str[i]);
		if (!str[i])
		{
			ft_putstr_fd("minishell: unclosed quotes\n", 2);
			return (1);
		}
		i++;
	}
}
