/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ultrasplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:08:45 by glopez-m          #+#    #+#             */
/*   Updated: 2024/02/25 16:29:31 by glopez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	count_words(const char *str, char *separators)
{
	int	i;
	int	amount;

	i = 0;
	amount = 0;
	while (str[i])
	{
		if (!ft_strchr(separators, str[i]))
		{
			amount++;
			while (str[i + 1] && !ft_strchr(separators, str[i]))
				i++;
		}
		i++;
	}
	return (amount);
}

static int	ft_size_word(char const *str, char *separators, int i)
{
	int	size;

	size = 0;
	while (!ft_strchr(separators, str[i]) && str[i])
	{
		size++;
		i++;
	}
	return (size);
}

static void	ft_free(char **strs, int j)
{
	while (j-- > 0)
		free(strs[j]);
	free(strs);
}

static int	loop(const char *str, char ***split, const int words,
		char *separators)
{
	int				size;
	int				i;
	int				j;

	i = 0;
	j = -1;
	while (++j < words)
	{
		while (ft_strchr(separators, str[i]))
			i++;
		size = ft_size_word(str, separators, i);
		(*split)[j] = ft_substr(str, i, size);
		if ((*split)[j] == NULL)
		{
			ft_free(*split, j);
			return (0);
		}
		i += size;
	}
	(*split)[j] = 0;
	return (1);
}

char	**ultrasplit(char const *str, char *separators)
{
	char			**split;
	const int		words = count_words(str, separators);

	if (!str)
		return (0);
	split = malloc((words + 1) * sizeof (char *));
	if (split == NULL)
		return (NULL);
	if (!loop(str, &split, words, separators))
		return (0);
	return (split);
}
