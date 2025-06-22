/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:16:26 by yel-alja          #+#    #+#             */
/*   Updated: 2025/06/22 15:43:17 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd *lst_new_cmd(char *cmd ,char **args , t_redir *red)
{
    t_cmd *tmp;
    
    tmp = malloc(sizeof(t_cmd));
    // garbage_collect(tmp);
    tmp->cmd = cmd;
    tmp->args = args;
    tmp->redirects = red;
    tmp->next = NULL;
    return(tmp);
}

t_redir *lst_new_red(char *file , t_type type)
{
    t_redir *tmp;
    
    tmp = malloc(sizeof(t_redir));
    // garbage_collect(tmp);
    tmp->file_del = file;
    tmp->type = type;
    tmp->next = NULL;
    return(tmp);
}

void lst_add_back(t_redir **head, t_redir *node)
{
    t_redir *tmp;

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

void lst_addbackc(t_cmd **head, t_cmd *node)
{
    t_cmd *tmp;

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
