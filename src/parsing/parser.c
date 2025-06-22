/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 01:57:44 by yel-alja          #+#    #+#             */
/*   Updated: 2025/06/23 00:13:28 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int count_args(t_token *token)
{
    int i = 0;
    while(token && token->type != PIPE)
    {
        if(token->type == WORD)
            i++;
        else
            token = token->next;
        token = token->next;
    }
    return (i);
}

t_cmd *parser2(t_token **tkn)
{
    t_redir *tmp = NULL;
    t_redir *red = NULL;
    t_cmd   *cmd = NULL;
    t_token *token = (*tkn);
    char *cmnd = ft_strdup(token->value);
    char **args = malloc(count_args(token) * 8);
    int i  = 0;
    while(token)
    {
        if(token->type == PIPE)
            break;
        else if(token->type != HEREDOC && token->type != OUTPUT && token->type != INPUT
            && token->type != APPEND)
            {
                args[i] = ft_strdup(token->value);
                        i++;
            }
        else if(token->type == HEREDOC)
        {
            if(token->next->quote)
                tmp = lst_new_red(token->next->value , HEREDOC_Q);
            else
                tmp = lst_new_red(token->next->value , HEREDOC);
        }
        else if(token->type == OUTPUT)
            tmp = lst_new_red(token->next->value, OUTPUT);
        else if(token->type == INPUT)
            tmp = lst_new_red(token->next->value, INPUT);
        else if(token->type == APPEND)
            tmp = lst_new_red(token->next->value, APPEND);
        if(tmp)
        {
            lst_add_back(&red, tmp);
            tmp = NULL;
        }
        token = token->next;
    }
    args[i] = NULL;
    cmd = lst_new_cmd(cmnd , args , red);
    (*tkn) = token;
    return (cmd);
}

t_cmd *parser(t_token *token)
{
    t_cmd *cmd = NULL;
    while(token)
    {
        if(token->type == PIPE)
            token = token->next;
        if(!token)
            break;
        lst_addbackc(&cmd , parser2(&token));
    }
    return (cmd);
}