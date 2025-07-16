/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:16:26 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/16 11:43:57 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd *new_cmd(char *cmd ,char **args , t_redir *red)
{
    t_cmd *tmp;

    tmp = malloc(sizeof(t_cmd));
    garbage_collect(tmp , true);
    tmp->cmd = cmd;
    tmp->args = args;
	tmp->fd_input = STDIN_FILENO;
	tmp->fd_output = STDOUT_FILENO;
	tmp->error = false;
	tmp->pid = 0;
    tmp->redirects = red;
    tmp->next = NULL;
    return(tmp);
}

t_redir *new_red(char *file , t_type type)
{
    t_redir *tmp;

    tmp = malloc(sizeof(t_redir));
    garbage_collect(tmp , true);
    tmp->filename = file;
    tmp->type = type;
    tmp->quoted = 0;
    tmp->next = NULL;
    return(tmp);
}

void red_add_back(t_redir **head, t_redir *node)
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

void cmd_add_back(t_cmd **head, t_cmd *node)
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
