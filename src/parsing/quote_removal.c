/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:59:32 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/20 12:21:51 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_quoted_word(char *str, int *i)
{
	char	quote;
	char	*rslt;
	int		len;

	len = 0;
	quote = str[(*i)++];
	while (str[(*i) + len] != quote && str[(*i) + len])
		len++;
	rslt = ft_substr(str + (*i), 0, len);
	(*i) += len + 1;
	return (rslt);
}

char	*get_word(char *str, int *i)
{
	char	*rslt;
	int		len;

	len = 0;
	while (str[(*i) + len] != '"' && str[(*i) + len] != '\'' && str[(*i) + len])
		len++;
	rslt = ft_substr(str + (*i), 0, len);
	(*i) += len;
	return (rslt);
}

char	*quote_removal(char *str)
{
	int		i;
	char	*rslt;

	rslt = NULL;
	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			rslt = ft_strjoin(rslt, get_quoted_word(str, &i));
		else
			rslt = ft_strjoin(rslt, get_word(str, &i));
	}
	return (rslt);
}

char	**init_vars(t_redir **r, t_cmd **cmd, char **cmnd, t_token *tkn)
{
	char	**args;

	*r = NULL;
	*cmd = NULL;
	*cmnd = get_cmd_name(tkn);
	args = malloc((count_args(tkn) + 1) * 8);
	garbage_collect(args, true);
	return (args);
}
