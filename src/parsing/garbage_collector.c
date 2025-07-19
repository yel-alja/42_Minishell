/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:11:52 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/18 11:39:45 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_garbage *lst(void *ptr)
{
    t_garbage *node;

    node = malloc(sizeof(t_garbage));
    if(!node)
        garbage_collect(NULL, true);
    node->ptr = ptr;
    node->next = NULL;
    return (node);
}

void free_list(t_garbage *lst)
{
    t_garbage *tmp;

	if (!lst)
		return;
    while(lst)
    {
        tmp = lst;
        lst = lst->next;
        if (tmp->ptr)
			free(tmp->ptr);
        if (tmp)
			free(tmp);
    }
}

void garbage_collect(void *ptr ,bool terminate) // every time we allocate somthing using malloc or split or strdup ...
{                               // we must give the garbage collector the adress that we allocate
    static t_garbage *head;
    t_garbage *tmp;

    tmp = NULL;
    if(ptr != NULL)
    {
        if(head == NULL)
            head = lst(ptr);
        else
        {
            tmp = head;
            while(tmp->next)
                tmp = tmp->next;
            tmp->next = lst(ptr);
        }
    }
    else
    {
        free_list(head);
        head = NULL;
        if(terminate == true) // if was true exit from program
            exit((free_env(), EXIT_FAILURE));
    }
}
