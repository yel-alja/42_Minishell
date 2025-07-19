/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 01:57:44 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/19 14:02:22 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_args(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD)
			i++;
		else
			token = token->next;
		token = token->next;
	}
	return (i);
}

char	*get_cmd_name(t_token *token)
{
	char	*cmd;

	while (token)
	{
		if (token->type == PIPE)
			return (NULL);
		if (token->type == WORD || token->type == AMBG)
		{
			if (token->type == WORD && (token->value[0] || token->quoted))
			{
				cmd = ft_strdup(token->value);
				return (cmd);
			}
			token = token->next;
		}
		else
			token = token->next->next;
	}
	return (NULL);
}

t_cmd	*parser2(t_token **tkn)
{
	t_redir	*tmp;
	t_redir	*red;
	t_cmd	*cmd;
	t_token	*token;
	char	*cmnd;
	char	**args;
	int		i;

	tmp = NULL;
	red = NULL;
	cmd = NULL;
	token = (*tkn);
	cmnd = get_cmd_name(token);
	args = malloc((count_args(token) + 1) * 8);
	garbage_collect(args, true);
	i = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD)
		{
			if (token->value[0] || token->quoted)
				args[i++] = ft_strdup(token->value);
		}
		else if (token->type == HEREDOC)
		{
			tmp = new_red(token->next->value, HEREDOC);
			if (token->next->quoted)
				tmp->quoted = 1;
		}
		else if (token->type == OUTPUT)
			tmp = new_red(token->next->value, OUTPUT);
		else if (token->type == INPUT)
			tmp = new_red(token->next->value, INPUT);
		else if (token->type == APPEND)
			tmp = new_red(token->next->value, APPEND);
		else if (token->type == AMBG)
			tmp = new_red("", AMBG);
		if (tmp)
		{
			red_add_back(&red, tmp);
			tmp = NULL;
		}
		if (token->type != HEREDOC && token->type != OUTPUT
			&& token->type != INPUT && token->type != APPEND
			&& token->type != AMBG)
			token = token->next;
		else
			token = token->next->next;
	}
	args[i] = NULL;
	cmd = new_cmd(cmnd, args, red);
	(*tkn) = token;
	return (cmd);
}

int	open_her(t_cmd *cmd)
{
	t_redir	*red;

	while (cmd)
	{
		red = cmd->redirects;
		while (red)
		{
			if (red->type == HEREDOC)
			{
				red->filename = heredoc_file(red->filename, red->quoted);
				if (!red->filename)
					return (1);
			}
			red = red->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

t_cmd	*parser(t_token *token)
{
	t_cmd	*cmd;

	cmd = NULL;
	if (!token)
		return (NULL);
	while (token)
	{
		if (token->type == PIPE)
			token = token->next;
		if (!token)
			break ;
		cmd_add_back(&cmd, parser2(&token));
	}
	if (open_her(cmd))
		return (NULL);
	return (cmd);
}
