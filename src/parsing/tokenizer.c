/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:17:00 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/07 18:19:08 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token *new_token(char *input, t_type type)
{
    t_token *node;

    node = malloc(sizeof(t_token));
    garbage_collect(node , 0);
    node->value = ft_strdup(input);
    garbage_collect(node->value , 0);
    node->type = type;
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

    tmp = new_token("|", PIPE);
    *i += 1;
    return (tmp);
}

t_token *token_re_input(int *i, char c)
{
    t_token *tmp;

    if (c != '<')
    {
        tmp = new_token("<", INPUT);
        *i += 1;
    }
    else
    {
        tmp = new_token("<<", HEREDOC);
        *i += 2;
    }
    return (tmp);
}

t_token *token_re_output(int *i, char c)
{
    t_token *tmp;
    if (c != '>')
    {
        tmp = new_token(">", OUTPUT);
        *i += 1;
    }
    else
    {
        tmp = new_token(">>", APPEND);
        *i += 2;
    }
    return (tmp);
}


char	*quoted_word(char *input, int *i, char *quote ,t_env *env)
{
	char	*str;
	int		len;

	(*i)++;
	len = ft_charlen(input + (*i), quote);
	str = ft_substr(input + (*i), 0, len );
    garbage_collect(str , 0);
	(*i) += len + 1;
    if(quote[0] == '"')
    {
        str = expansion(str ,env, 0);
    }
	return (str);
}

char	*unquoted_word(char *input, int *i , t_env *env)
{
	char	*str;
	int		len;

	len = 0;
	while (input[(*i) + len] && !is_whitespace(input[(*i) + len]) && !is_metachar(input[(*i) + len]))
		len++;
	str = ft_substr(input + (*i), 0, len);
    garbage_collect(str , 0);
    str = expansion(str ,env ,1);
	(*i) += len;
	return (str);
}

t_token *token_word(char *input, int *i , t_env *env)
{
    char *str;
    t_token *token = NULL;

	str = NULL;
    while (input[*i] && !is_whitespace(input[*i]))
    {
        if(input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
            break;
        if (input[*i] == '"')
        {
            str = ft_strjoin(str, quoted_word(input, i, "\"" , env));
            garbage_collect(str , 0);
        }
        else if (input[*i] == '\'')
        {   
            str = ft_strjoin(str, quoted_word(input, i, "'", env));
            garbage_collect(str , 0);
        }
		else
        {
            str = ft_strjoin(str, unquoted_word(input, i, env));
            garbage_collect(str , 0);
        }
    }
    if(str)
        token = new_token(str, WORD);
    return (token);
}

t_token *build_list(char **res)
{
    int i = 0;
    t_token *head = NULL;
    while(res[i])
    {
        token_add_back(&head , new_token(res[i] , WORD));
        i++;   
    }
    return (head);
}
t_token *handling_token(char *input, int *i , t_env *env)
{
    t_token *token = NULL;
    char **res;
    if (input[*i] == '\0')
        return (NULL);
    if (input[*i] == '|')
        token = token_pipe(i);
    else if (input[*i] == '<')
        token = token_re_input(i, input[*i + 1]);
    else if (input[*i] == '>')
        token = token_re_output(i, input[*i + 1]);
    else
    {
        token = token_word(input, i ,env);
        if(token->value && ft_strchr(token->value , 14))
        {
            // printf("===={%s}\n" , token->value);
            res = ft_split(token->value , 14); //?
            token = build_list(res);
        }
    }
    return (token);
}

t_token *tokenizer(char *input , t_env *env)
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
        token_add_back(&head, handling_token(input, &i , env));
    }
    if(!check_syntax(head))
        return NULL;
    return head;
}
