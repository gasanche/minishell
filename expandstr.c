/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:29:09 by glopez-m          #+#    #+#             */
/*   Updated: 2024/02/28 20:28:23 by glopez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	_update_status(int *status, int *i, t_piece **now, int flag)
{
	*status = *status ^ flag;
	*i += 1;
	(*now)->next = newpiece(*status | flag, ft_strdup(""), 0);
}

void	_get_str(char *str, int *i, int status, t_piece *piece)
{
	int		j;

	j = *i + 1;
	while (str[j] != '\"' && str[j] != '\'' && str[j] != '$' && str[j])
		j++;
	piece->next = newpiece(status, ft_substr(str, *i, j - *i), 0);
	*i = j;
}

t_piece	*_envvar(int *i, int status, char **env, char *str)
{
	t_piece	*temp;

	temp = getexpansion(env, &(str[*i + 1]), status);
	*i += explen(&str[*i + 1]) + 1;
	return (temp);
}

void	_dollar_char(int *i, int status, char *str, t_piece *piece)
{
	piece->next = newpiece(status, str, 0);
	*i += 2;
}

t_piece	*expandstr(char *str, char **env, int exstatus, int status)
{
	t_piece	*first;
	t_piece	*now;
	int		i;

	first = newpiece(0, ft_strdup(""), 0);
	now = first;
	i = 0;
	while (str[i])
	{
		if (!((status & P_DQT)) && str[i] == '\'')
			_update_status(&status, &i, &now, P_SQT);
		else if ((!(status & P_SQT)) && str[i] == '\"')
			_update_status(&status, &i, &now, P_DQT);
		else if ((!(status & P_SQT)) && str[i] == '$'
			&& (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
			now->next = _envvar(&i, status, env, str);
		else if (!(status & P_SQT) && str[i] == '$' && str[i + 1] == '?')
			_dollar_char(&i, status, ft_itoa(exstatus), now);
		else if (!(status & P_SQT) && str[i] == '$' && ft_isdigit(str[i + 1]))
			_dollar_char(&i, status | P_EXP, ft_strdup(""), now);
		else
			_get_str(str, &i, status, now);
		now = last_piece(now);
	}
	return (cleanpieces(&first));
}
