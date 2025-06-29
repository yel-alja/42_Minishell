/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:17:00 by yel-alja          #+#    #+#             */
/*   Updated: 2025/06/25 22:23:53 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token *lst_new(char *input, t_type type)
{
    t_token *node;

    node = malloc(sizeof(t_token));
    // garbage_collect(node);
    node->value = ft_strdup(input);
    // garbage_collect(node->value);
    node->type = type;
    node->quote = 0;
    node->next = NULL;
    return (node);
}

void lst_addback(t_token **head, t_token *node)
{
    t_token *tmp;

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

t_token *_pipe(int *i)
{
    t_token *tmp;

    tmp = lst_new("|", PIPE);
    *i += 1;
    return (tmp);
}

t_token *_heredoc_in(int *i, char c)
{
    t_token *tmp;

    if (c != '<')
    {
        tmp = lst_new("<", INPUT);
        *i += 1;
    }
    else
    {
        tmp = lst_new("<<", HEREDOC);
        *i += 2;
    }
    return (tmp);
}

t_token *_app_out(int *i, char c)
{
    t_token *tmp;
    if (c != '>')
    {
        tmp = lst_new(">", OUTPUT);
        *i += 1;
    }
    else
    {
        tmp = lst_new(">>", APPEND);
        *i += 2;
    }
    return (tmp);
}


char	*_double_quotes(char *input, int *i)
{
	char	*str;
	int		len;
    t_token *token;
	(*i)++;
	len = ft_charlen(input + (*i), '"');
	str = ft_substr(input + (*i) - 1, 0, len + 2);
	(*i) += len + 1;
    // str = expansion(str);
	return (str);
}

char	*_single_quotes(char *input, int *i)
{
	char	*str;
	int		len;

	(*i)++;
	len = ft_charlen(input + (*i), '\'');
	str = ft_substr(input + (*i) - 1, 0, len + 2);
    garbage_collect(str);
	(*i) += len + 1;
	return (str);
}

char	*_simple_word(char *input, int *i)
{
	char	*str;
	int		len;
    t_token *token;
	len = 0;
	while (input[(*i) + len] && !is_whitespace(input[(*i) + len]) && !is_metachar(input[(*i) + len]))
		len++;
	str = ft_substr(input + (*i), 0, len);
    // garbage_collect(str);
    // str = expansion(str);
	(*i) += len;
	return (str);
}

t_token *handling_word(char *input, int *i)
{
    char *str;
    t_token *token;
    int quote = 0;

	str = NULL;
    while (input[*i] && !is_whitespace(input[*i]))
    {
        if(input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
            break;
        if (input[*i] == '"')
        {
            quote = 1;
            str = ft_strjoin(str, _double_quotes(input, i));
        }
        else if (input[*i] == '\'')
        {
            quote = 2;    
			str = ft_strjoin(str, _single_quotes(input, i));
        }
		else
            str = ft_strjoin(str, _simple_word(input, i));
    }
    if(str)
    {
        token = lst_new(str, WORD);
        token->quote = quote;
    }
    return (token);
}

t_token *check_operator(char *input, int *i)
{
    t_token *token = NULL;
	int j;

    if (input[*i] == '\0')
        return (NULL);
    if (input[*i] == '|')
        token = _pipe(i);
    else if (input[*i] == '<')
        token = _heredoc_in(i, input[*i + 1]);
    else if (input[*i] == '>')
        token = _app_out(i, input[*i + 1]);
    else
        token = handling_word(input, i);
    return (token);
}

t_token *tokenizer(char *input)
{
    t_token *head = NULL;
    int i = 0;
    if(!check_quotes(input))
        return (head);
    while (input[i])
    {
        while (input[i] && is_whitespace(input[i]))
            i++;
        if(!input[i])
            break;
        lst_addback(&head, check_operator(input, &i));
    }
    if(!check_syntax(head))
        return NULL;
    return head;
}
