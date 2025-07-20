/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 00:54:06 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/20 00:55:12 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*her_del(char *input, int *i)
{
	int		start;
	char	*del;
	size_t	len;
	t_token	*tmp;

	while (input[*i] && is_whitespace(input[*i]))
		*i += 1;
	start = *i;
	while (input[start] && input[start] != '>' && input[start] != '<'
		&& input[start] != '|' && !is_whitespace(input[start]))
		start++;
	del = ft_substr(input, *i, start - *i);
	len = ft_strlen(del);
	*i += len;
	del = quote_removal(del);
	if (!del)
		return (NULL);
	tmp = new_token(del, WORD, 0);
	if (len != ft_strlen(del))
		tmp->quoted = 1;
	return (tmp);
}

t_token	*token_re_input(int *i, char *c)
{
	t_token	*tmp;

	tmp = NULL;
	if (c[*i + 1] != '<')
	{
		tmp = new_token("<", INPUT, 0);
		*i += 1;
	}
	else
	{
		tmp = new_token("<<", HEREDOC, 0);
		*i += 2;
		token_add_back(&tmp, her_del(c, i));
	}
	return (tmp);
}

t_token	*token_re_output(int *i, char c)
{
	t_token	*tmp;

	if (c != '>')
	{
		tmp = new_token(">", OUTPUT, 0);
		*i += 1;
	}
	else
	{
		tmp = new_token(">>", APPEND, 0);
		*i += 2;
	}
	return (tmp);
}

char	*quoted_word(char *input, int *i, char *quote)
{
	char	*str;
	int		len;

	(*i)++;
	len = ft_charlen(input + (*i), quote);
	str = ft_substr(input + (*i), 0, len);
	(*i) += len + 1;
	if (quote[0] == '"')
	{
		str = expansion(str, 0);
	}
	return (str);
}

char	*unquoted_word(char *input, int *i)
{
	char	*str;
	int		len;

	len = 0;
	while (input[(*i) + len] && !is_whitespace(input[(*i) + len])
		&& !is_metachar(input[(*i) + len]))
		len++;
	str = ft_substr(input + (*i), 0, len);
	str = expansion(str, 1);
	(*i) += len;
	if (str[0] == '\0')
	{
		return (NULL);
	}
	return (str);
}
