/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:17:00 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/20 09:42:16 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*token_pipe(int *i)
{
	t_token	*tmp;

	tmp = new_token("|", PIPE, 0);
	*i += 1;
	return (tmp);
}

char	*extract_word(int *i, char *input, int *flag)
{
	char	*str;

	str = NULL;
	while (input[*i] && !is_whitespace(input[*i]))
	{
		if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
			break ;
		if (input[*i] == '"')
		{
			str = ft_strjoin(str, quoted_word(input, i, "\""));
			*flag = 1;
		}
		else if (input[*i] == '\'')
		{
			str = ft_strjoin(str, quoted_word(input, i, "'"));
			*flag = 1;
		}
		else
			str = ft_strjoin(str, unquoted_word(input, i));
	}
	return (str);
}

t_token	*token_word(char *input, int *i)
{
	char	*str;
	t_token	*token;
	int		flag;

	flag = 0;
	token = NULL;
	str = extract_word(i, input, &flag);
	if (str)
	{
		token = new_token(str, WORD, 0);
		token->quoted = flag;
	}
	return (token);
}

t_token	*handling_token(char *input, int *i)
{
	t_token	*token;
	char	**res;

	token = NULL;
	if (input[*i] == '|')
		token = token_pipe(i);
	else if (input[*i] == '<')
		token = token_re_input(i, input);
	else if (input[*i] == '>')
		token = token_re_output(i, input[*i + 1]);
	else
	{
		token = token_word(input, i);
		if (token && token->value && ft_strchr(token->value, 14))
		{
			res = ft_split(token->value, 14);
			if (res)
				token = build_list(res);
		}
	}
	return (token);
}

t_token	*tokenizer(char *input)
{
	t_token	*head;
	int		*status;
	int		i;

	head = NULL;
	status = get_addr_exit_status(NULL);
	i = 0;
	if (!check_quotes(input))
		return ((*status = 2), NULL);
	while (input[i])
	{
		while (input[i] && is_whitespace(input[i]))
			i++;
		if (!input[i])
			break ;
		token_add_back(&head, handling_token(input, &i));
	}
	if (!check_syntax(head))
		return ((*status = 2), NULL);
	update_amg(head);
	return (head);
}
