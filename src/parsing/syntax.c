/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:32:56 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/19 12:14:40 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	into_quote(char *input, int *i, char c)
{
	*i += 1;
	while (input[*i])
	{
		if (input[*i] == c)
			return (1);
		*i += 1;
	}
	return (0);
}

int	check_quotes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"')
		{
			if (!into_quote(input, &i, '"'))
				return (errmsg("syntax error", NULL, "unclosed double quotes"),
					0);
		}
		else if (input[i] == '\'')
		{
			if (!into_quote(input, &i, '\''))
				return (errmsg("syntax error", NULL, "unclosed single quotes"),
					0);
		}
		i++;
	}
	return (1);
}

int	check_syntax(t_token *token)
{
	if (!token)
		return (1);
	if (token->type == PIPE)
		return (errmsg(NULL, NULL, "syntax error"), 0);
	while (token)
	{
		if (token->type == PIPE && token->next && token->next->type == PIPE)
			return (errmsg(NULL, NULL, "syntax error"), 0);
		if ((is_operator(token) || token->type == PIPE) && token->next == NULL)
			return (errmsg(NULL, NULL, "syntax error"), 0);
		if ((is_operator(token)) && (is_operator(token->next)
				|| token->next->type == PIPE))
			return (errmsg(NULL, NULL, "syntax error"), 0);
		token = token->next;
	}
	return (1);
}
