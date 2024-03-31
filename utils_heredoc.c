/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:10:34 by glopez-m          #+#    #+#             */
/*   Updated: 2024/02/29 12:12:45 by glopez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	_incrementname(char	**name)
{
	char		*temp;
	const int	first = 9;
	int			i;

	i = 0;
	(*name)[first]++;
	while ((*name)[first + i] > 'z')
	{
		(*name)[first + i] = 'a';
		if ((*name)[first + i + 1])
		{
			++(*name)[first + i + 1];
			i++;
		}
		else
		{
			temp = ft_strjoin(*name, "a");
			if (!temp)
				pterr((char *[2]){"minishell: ", 0},
					ERR_EXIT | ERR_PROR, ENOMEM);
			free(*name);
			*name = temp;
		}
	}
}

char	*findname(void)
{
	char	*name;

	name = ft_strdup("/tmp/hdc_a");
	if (!name)
		pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, ENOMEM);
	while (!(access(name, F_OK) == -1))
	{
		if (errno == ENAMETOOLONG)
			pterr((char *[2]){
				"minishell: failed to find unused name for heredoc", 0},
				ERR_EXIT | ERR_PROR, PERR_EEX);
		_incrementname(&name);
	}
	return (name);
}

char	*get_term(char *given)
{
	char	*term;
	int		ind_t;
	int		ind_g;
	int		size;

	term = ft_calloc(ft_strlen(given) + 1, sizeof (char));
	if (!term)
		pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, ENOMEM);
	ind_g = 0;
	ind_t = 0;
	while (given[ind_g])
	{
		if (given[ind_g] == '\'' || given[ind_g] == '\"')
		{
			size = skip_until_next(&given[ind_g]);
			ft_memcpy(&term[ind_t], &given[ind_g + 1], size - 1);
			ind_t += size - 1;
			ind_g += size + 1;
		}
		else
			term[ind_t++] = given[ind_g++];
	}
	return (term);
}
