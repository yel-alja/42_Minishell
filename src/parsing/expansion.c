/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 09:06:36 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/20 10:39:36 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'
				|| str[i + 1] == '?'))
			return (1);
		i++;
	}
	return (0);
}

char	*flag_splitters(char *value)
{
	int		i;
	char	*res;

	if (!value)
		return (NULL);
	i = 0;
	res = malloc(ft_strlen(value) + 1);
	garbage_collect(res, true);
	while (value[i])
	{
		if (value[i] == '\n' || value[i] == ' ' || value[i] == '\t')
			res[i] = 14;
		else
			res[i] = value[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

void	name_len(char *token, int *start, int i)
{
	if (token[i] == '?')
		*start = i + 1;
	else
	{
		*start = i;
		while (token[*start] && (ft_isalnum(token[*start])
				|| token[*start] == '_') && !is_whitespace(token[*start])
			&& token[*start] != '$')
			(*start)++;
	}
}

char	*var(char *token, int flag, int i, int start)
{
	char	*var_name;
	char	*var_value;
	char	*p;

	p = NULL;
	while (token[i])
	{
		if (token[i] == '$' && (ft_isalpha(token[i + 1]) || token[i + 1] == '_'
				|| token[i + 1] == '?'))
		{
			i++;
			name_len(token, &start, i);
			p = ft_substr(token, 0, i - 1);
			var_name = ft_substr(token, i - 1, start - i + 1);
			var_value = ft_getenv(var_name + 1);
			if (flag == 1)
				var_value = flag_splitters(var_value);
			p = ft_strjoin(p, var_value);
			p = ft_strjoin(p, token + start);
			i += ft_strlen(var_value) - 2;
			token = p;
		}
		i++;
	}
	return (p);
}

char	*expansion(char *token, int flag)
{
	char	*res;
	int		i;
	int		start;

	start = 0;
	i = 0;
	res = NULL;
	if (!check_dollar(token))
		return (token);
	res = var(token, flag, i, start);
	return (res);
}
