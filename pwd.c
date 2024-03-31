/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:38:57 by glopez-m          #+#    #+#             */
/*   Updated: 2024/02/29 14:14:32 by gabsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	pwd(void)
{
	char	*check;

	check = getcwd(NULL, 0);
	if (!check)
		pterr((char *[2]){"minishell: ", 0}, ERR_PROR, 1);
	else
	{
		printf("%s\n", check);
		free(check);
	}
	return (0);
}
/*
int	main()
{
	pwd();
	return 0;
}*/
