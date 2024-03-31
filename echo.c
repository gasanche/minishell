/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:56:38 by glopez-m          #+#    #+#             */
/*   Updated: 2024/03/09 19:10:53 by gabsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	check_flag(char **str, int *flag)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (str[i][1] == '\0')
		return (1);
	while (str[i][j] == 'n')
		j++;
	if (str[i][j] != '\0')
		return (1);
	else
		*flag = 1;
	return (0);
}

int	echo(t_egg *info)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (!info->cmdargv[1])
		write(1, "\n", 1);
	else
	{
		while (info->cmdargv[i] && info->cmdargv[i][0] == '-'
				&& !check_flag(&info->cmdargv[i], &flag))
			i++;
		while (info->cmdargv[i])
		{
			printf("%s", info->cmdargv[i]);
			if (info->cmdargv[i + 1])
				printf(" ");
			i++;
		}
		if (flag == 0)
			printf("\n");
	}
	return (0);
}
