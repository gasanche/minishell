/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isstrin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:58:36 by glopez-m          #+#    #+#             */
/*   Updated: 2024/02/21 18:49:18 by glopez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	isstrin(char *str, const char **phrase)
{
	int	i;
	int	j;

	if (!str)
		return (0);
	i = -1;
	while (phrase[++i])
	{
		j = 0;
		while (phrase[i][j] && str[j] && phrase[i][j] == str[j])
			j++;
		if (!phrase[i][j] && !str[j])
			return (1);
	}
	return (0);
}
