/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 01:57:44 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/16 11:44:24 by zouazrou         ###   ########.fr       */
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

char *get_cmd_name(t_token *token)
{
    char *cmd;
    while(token)
    {
        if(token->type == PIPE)
            return NULL;
        if(token->type == WORD)
        {
            cmd = ft_strdup(token->value);
            return(cmd);
        }
        else
            token = token->next->next;
    }
    return (NULL);
}
// ambg should added to re list | exit status $? |<

t_cmd *parser2(t_token **tkn)
{
    t_redir *tmp = NULL;
    t_redir *red = NULL;
    t_cmd   *cmd = NULL;
    t_token *token = (*tkn);
    char *cmnd = get_cmd_name(token);
    char **args = malloc((count_args(token) + 1) * 8);
    garbage_collect(args , true);
    int i  = 0;
    while(token)
    {
        if(token->type == PIPE)
            break;
        else if(token->type == WORD)
            {
                args[i] = ft_strdup(token->value);
                        i++;
            }
        else if(token->type == HEREDOC)
        {
            tmp = new_red(token->next->value , HEREDOC);
            if(token->next->quoted)
                tmp->quoted = 1;
        }
        else if(token->type == OUTPUT)
                tmp = new_red(token->next->value, OUTPUT);
        else if(token->type == INPUT)
                tmp = new_red(token->next->value, INPUT);
        else if(token->type == APPEND)
                tmp = new_red(token->next->value, APPEND);
        else if(token->type == AMBG)
                tmp = new_red("", AMBG);
        if(tmp)
        {
            red_add_back(&red, tmp);
            tmp = NULL;
        }
        if(token->type != HEREDOC && token->type != OUTPUT && token->type != INPUT
            && token->type != APPEND)
            token = token->next;
        else
            token = token->next->next;
    }
    args[i] = NULL;
    cmd = new_cmd(cmnd , args , red);
    (*tkn) = token;
    return (cmd);
}

void open_her(t_cmd *cmd)
{
    t_redir *red;
    while(cmd)
    {
        red = cmd->redirects;
        while (red)
        {
            if(red->type == HEREDOC)
            {
                red->filename = heredoc_file(red->filename  , red->quoted);
            }
            red = red->next;
        }
        cmd = cmd->next;

    }
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
        cmd_add_back(&cmd , parser2(&token));
    }
    open_her(cmd );
    return (cmd);
}
