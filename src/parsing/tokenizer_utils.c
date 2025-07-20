/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 00:49:17 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/20 09:45:19 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*new_token(char *input, t_type type, int amg)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	garbage_collect(node, true);
	node->value = ft_strdup(input);
	node->type = type;
	node->amg = amg;
	node->quoted = 0;
	node->next = NULL;
	return (node);
}

void	token_add_back(t_token **head, t_token *node)
{
	t_token	*tmp;

	if (*head == NULL)
		*head = node;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

t_token	*build_list(char **res)
{
	int		i;
	t_token	*head;

	i = 0;
	head = NULL;
	while (res[i])
	{
		token_add_back(&head, new_token(res[i], WORD, 1));
		i++;
	}
	return (head);
}

void	update_amg(t_token *token)
{
	if (!token)
		return ;
	while (token->next)
	{
		if (token->type != HEREDOC && token->type != WORD && token->type != PIPE
			&& ((token->next->amg == 1 && token->next->next)
				|| (token->next->value[0] == '\0' && !token->next->quoted)))
			token->type = AMBG;
		token = token->next;
	}
}
