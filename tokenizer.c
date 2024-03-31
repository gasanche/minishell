/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabsanch <gabsanch@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:43:38 by gabsanch          #+#    #+#             */
/*   Updated: 2024/03/03 15:34:36 by glopez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	skip_until_next(char *str)
{
	const char	ref = str[0];
	int			i;

	i = 1;
	while (str[i] && str[i] != ref)
		i++;
	return (i);
}

int	add_word(char *str, int i, t_lexer *node)
{
	char	*word;
	int		j;

	j = 0;
	while (str[i + j] && (str[i + j] != ' '
			|| (9 <= str[i + j] && str[i + j] <= 13)))
	{
		if (str[i + j] == '\'' || str[i + j] == '\"')
			j += skip_until_next(&str[i + j]);
		if (istoken(str[i + j]) == 1)
			break ;
		j++;
	}
	word = ft_substr(str, i, j);
	if (!word)
		return (-1);
	node->word = word;
	return (j);
}

int	add_token(char *str, int i, t_lexer *node)
{
	char	*word;
	int		j;

	j = 0;
	if (str[i] == '|')
		node->token = '|';
	else if (str[i] == '<' && !istoken(str[i + 1]))
		node->token = RED_IN_S;
	else if (str[i] == '<' && str[i + 1] == '<')
		node->token = RED_IN_D;
	else if (str[i] == '>' && !istoken(str[i + 1]))
		node->token = RED_OUT_S;
	else if (str[i] == '>' && str[i + 1] == '>' && !istoken(str[i + 2]))
		node->token = RED_OUT_D;
	if (node->token == RED_IN_D || node->token == RED_OUT_D)
		j = 2;
	else
		j = 1;
	word = ft_substr(str, i, j);
	if (!word)
		return (-1);
	node->word = word;
	return (j);
}

int	set_node(t_lexer *arg, char *str, int i)
{
	if (istoken(str[i]))
		i += add_token(str, i, arg);
	else
		i += add_word(str, i, arg);
	return (i);
}

int	tokenize(char *str, t_lexer **lexer)
{
	t_lexer	*arg;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' || (9 <= str[i] && str[i] <= 13))
		{
			arg = ft_calloc(1, sizeof (t_lexer));
			if (!arg)
				return (-1);
			ft_lxr_addback(lexer, arg);
			i = set_node(arg, str, i);
			if (i == -1)
				return (-1);
		}
		else
			i++;
	}
	return (1);
}
