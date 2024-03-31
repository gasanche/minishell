/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokencheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-m <glopez-m@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:04:46 by glopez-m          #+#    #+#             */
/*   Updated: 2024/03/09 18:36:11 by glopez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	hd_mockup(t_lexer *list, t_common *common, char *token)
{
	t_lexer	*now;
	char	*tmp;

	if (token)
		pterr((char *[5]){"minishell: syntax error near unexpected token `",
			token, "'", 0}, 0, 0);
	now = list;
	while (!g_received && now && (now->token & RED_IN_D)
		&& now->next && !now->next->token)
	{
		tmp = create_hd(now->next->word, common);
		unlink(tmp);
		now = now->next->next;
	}
	if (!g_received && !token)
		ft_putstr_fd("minishell: syntax error near unexpected \
token `newline'\n", 2);
	return (1);
}

int	checktokenerrs(t_lexer *lexed, t_common *common)
{
	t_lexer	*now;
	int		err;

	err = 0;
	if (lexed->token == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		err = 1;
	}
	now = lexed;
	while (now && !err)
	{
		if (now->token)
		{
			if (!now->next)
				err = hd_mockup(lexed, common, 0);
			else if (((now->token & RED_ANY) && now->next->token)
				|| (now->token == '|' && now->next->token == '|'))
				err = hd_mockup(lexed, common, now->next->word);
		}
		now = now->next;
	}
	if (err && !g_received)
		common->exstatus = 258;
	return (err);
}
