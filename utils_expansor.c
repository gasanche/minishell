/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 20:15:44 by glopez-m          #+#    #+#             */
/*   Updated: 2024/03/13 18:12:37 by glopez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	explen(char *var)
{
	int	len;

	len = 0;
	while (var[len] && (ft_isalnum(var[len]) || var[len] == '_'))
		len++;
	return (len);
}

t_piece	*_splittopieces(char **tmpsplit, char status)
{
	t_piece	*expanded;
	t_piece	*now;
	int		i;

	expanded = newpiece(status, ft_strdup(tmpsplit[0]), 0);
	now = expanded;
	i = 0;
	while (tmpsplit[++i])
	{
		now->next = newpiece(status | P_SLT, ft_strdup(tmpsplit[i]), 0);
		now = now->next;
	}
	return (expanded);
}

t_piece	*getexpansion(char **env, char	*var, int status)
{
	char		*temp;
	char		*tmpsrc;
	char		**tmpsplit;
	t_piece		*ret;
	const int	len = explen(var);

	tmpsrc = ft_substr(var, 0, len);
	if (!tmpsrc)
		pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, ENOMEM);
	temp = ft_getenv(env, tmpsrc);
	free(tmpsrc);
	if (!temp)
		return (newpiece(status | P_EXP, ft_strdup(""), 0));
	if (!(status & P_DQT) && !(status & NO_WS))
	{
		tmpsplit = ultrasplit(temp, " 	\n");
		free(temp);
		ret = _splittopieces(tmpsplit, status);
		ft_free_ptr_array((void **) tmpsplit, ft_arraylen(tmpsplit), 1);
	}
	else
		ret = newpiece(status | P_EXP, temp, 0);
	return (ret);
}

t_piece	*expandcmd(char **cmdargv, const int argc, char **env, int exstatus)
{
	int		i;
	t_piece	*cumulative;
	t_piece	*cumul_last;

	cumulative = expandstr(cmdargv[0], env, exstatus, 0);
	cumul_last = cumulative;
	i = 1;
	while (cumul_last && cmdargv[i] && i < argc)
	{
		cumul_last->next = expandstr(cmdargv[i], env, exstatus, 0);
		while (cumul_last->next)
			cumul_last = cumul_last->next;
		i++;
	}
	return (cumulative);
}

char	**expanded_to_array(t_piece *expanded)
{
	int		i;
	char	**converted;
	t_piece	*now;

	if (expanded == 0)
		return (0);
	converted = malloc((piecelen(expanded) + 1) * sizeof (char *));
	if (!converted)
		pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, ENOMEM);
	now = expanded;
	i = 0;
	while (now)
	{
		converted[i] = ft_strdup(now->chunk);
		i++;
		now = now->next;
	}
	converted[i] = 0;
	scramble_pieces(&expanded);
	return (converted);
}
