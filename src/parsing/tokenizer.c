/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:17:00 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/16 09:21:27 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


t_token *new_token(char *input, t_type type , int amg)
{
    t_token *node;

    node = malloc(sizeof(t_token));
    garbage_collect(node , 0);
    node->value = ft_strdup(input);
    garbage_collect(node->value , 0);
    node->type = type;
    node->amg = amg;
    node->quoted = 0;
    node->next = NULL;
    return (node);
}

void token_add_back(t_token **head, t_token *node)
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


t_token *token_pipe(int *i)
{
    t_token *tmp;

    tmp = new_token("|", PIPE ,0);
    *i += 1;
    return (tmp);
}
t_token *her_del(char *input, int *i)
{
    int start;
    char *del;
    size_t len;
    t_token *tmp;
    while(input[*i] && is_whitespace(input[*i]))
        *i += 1;
    start = *i;
    while(input[start] && input[start] != '>' && input[start] != '<' && input[start] != '|' && !is_whitespace(input[start]))
        start++;
    del = ft_substr(input, *i , start - *i);
    len  = ft_strlen(del);
    *i += len;
    del = quote_removal(del);
    if(!del)
        return NULL;
    tmp = new_token(del, WORD, 0);
    if(len != ft_strlen(del))
        tmp->quoted = 1;
    return(tmp);
}

t_token *token_re_input(int *i, char *c)
{
    t_token *tmp = NULL;

    if (c[*i + 1] != '<')
    {
       tmp = new_token("<", INPUT , 0);
        *i += 1;
    }
    else
    {
        tmp = new_token("<<", HEREDOC , 0);
        *i += 2;
        token_add_back(&tmp, her_del(c , i));
    }
    return (tmp);
}

t_token *token_re_output(int *i, char c)
{
    t_token *tmp;

    if (c != '>')
    {
        tmp = new_token(">", OUTPUT , 0);
        *i += 1;
    }
    else
    {
        tmp = new_token(">>", APPEND , 0);
        *i += 2;
    }
    return (tmp);
}


char	*quoted_word(char *input, int *i, char *quote )
{
	char	*str;
	int		len;

	(*i)++;
	len = ft_charlen(input + (*i), quote);
	str = ft_substr(input + (*i), 0, len);
    garbage_collect(str , 0);
	(*i) += len + 1;
    if(quote[0] == '"')
    {
        str = expansion(str , 0);
    }
	return (str);
}

char	*unquoted_word(char *input, int *i  )
{
	char	*str;
	int		len;
	len = 0;
	while (input[(*i) + len] && !is_whitespace(input[(*i) + len]) && !is_metachar(input[(*i) + len]))
		len++;
	str = ft_substr(input + (*i), 0, len);
    garbage_collect(str , 0);
    str = expansion(str  ,1);
	(*i) += len;
    if(str[0] == '\0')
	{
		return NULL;
	}
	return (str);
}

t_token *token_word(char *input, int *i )
{
    char *str;
    t_token *token = NULL;
    int flag = 0;
	str = NULL;
    while (input[*i] && !is_whitespace(input[*i]))
    {
        if(input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
            break;
        if (input[*i] == '"')
        {
            str = ft_strjoin(str, quoted_word(input, i, "\"" ));
            flag = 1;
            garbage_collect(str , 0);
        }
        else if (input[*i] == '\'')
        {
            str = ft_strjoin(str, quoted_word(input, i, "'"));
            flag = 1;
            garbage_collect(str , 0);
        }
		else
        {
            str = ft_strjoin(str, unquoted_word(input, i));
            garbage_collect(str , 0);
        }
    }
    if(str)
    {
        token = new_token(str, WORD , 0);
        token->quoted = flag;
    }
    return (token);
}

t_token *build_list(char **res)
{
    int i = 0;
    t_token *head = NULL;
    while(res[i])
    {
        token_add_back(&head , new_token(res[i] , WORD , 1));
        i++;
    }
    return (head);
}

t_token *handling_token(char *input, int *i )
{
    t_token *token = NULL;
    char **res;

    if (input[*i] == '|')
        token = token_pipe(i);
    else if (input[*i] == '<')
        token = token_re_input(i, input);
    else if (input[*i] == '>')
        token = token_re_output(i, input[*i + 1]);
    else
    {
        token = token_word(input, i);
        if(token && token->value && ft_strchr(token->value , 14))
        {
            res = ft_split(token->value , 14);
            if(res)
                token = build_list(res);
        }
    }
    return (token);
}

void update_amg(t_token *token)
{
    while(token->next)
    {
        if(token->type != HEREDOC && token->type != WORD&& token->type != PIPE &&
            ((token->next->amg == 1  && token->next->next)|| token->next->value[0] == '\0'))
            token->type = AMBG;
        token = token->next;
    }
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
        token_add_back(&head, handling_token(input, &i ));
    }
    if(!check_syntax(head))
        return NULL;
    update_amg(head);
    return head;
}
