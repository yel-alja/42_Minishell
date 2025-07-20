/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 09:18:00 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/20 00:48:25 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_whitespace(char c)
{
	return (contains_char(c, WHITE_SP));
}

int	is_metachar(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '\'' || c == '"')
		return (1);
	return (0);
}

int	contains_char(char c, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (c == str[i])
			return (1);
	}
	return (0);
}

int	ft_charlen(char *str, char *del)
{
	int	len;

	len = 0;
	while (str[len] && !contains_char(str[len], del))
		len++;
	return (len);
}

int	is_operator(t_token *token)
{
	if (token->type != WORD && token->type != AMBG && token->type != PIPE)
		return (1);
	return (0);
}
