/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabsanch <gabsanch@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:11:42 by gabsanch          #+#    #+#             */
/*   Updated: 2024/03/16 17:39:14 by gabsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isexport(char c)
{
	return ((c == '+' || c == '='));
}

void	print_vars(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		ft_putstr_fd("declare -x ", 2);
		ft_putstr_fd(env[i], 2);
		ft_putstr_fd("\n", 2);
		i++;
	}
}

int	ft_print_not_valid(char *var, int *exstt)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	*exstt = 1;
	return (1);
}

int	ft_var_is_valid(char *first, int j)
{
	if (ft_isalpha(first[0]) || first[0] == '_')
	{
		while (first[j] && (ft_isalnum(first[j])
				|| first[j] == '_'))
			j++;
		return (j);
	}
	else
		return (0);
}

void	var_append(char *str, char **env, int i)
{
	char	*tmp;

	tmp = env[i];
	env[i] = ft_strjoin(env[i], str);
	if (!env[i])
		pterr((char *[2]){"minishell: ", 0}, ERR_EXIT | ERR_PROR, ENOMEM);
	free(tmp);
}
