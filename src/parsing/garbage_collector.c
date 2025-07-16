/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:11:52 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/15 18:04:55 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_garbage *lst(void *ptr)
{
    t_garbage *node;

    node = malloc(sizeof(t_garbage));
    if(!node)
        garbage_collect(NULL, 0);
    node->ptr = ptr;
    node->next = NULL;
    return (node);
}

void free_list(t_garbage *lst)
{
    t_garbage *tmp;

    while(lst)
    {
        tmp = lst;
        lst = lst->next;
        free(tmp->ptr);
        free(tmp);
    }
}

void garbage_collect(void *ptr ,int flag) // every time we allocate somthing using malloc or split or strdup ...  
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
        if(flag == 0) //it's mean malloc failed
            exit(EXIT_FAILURE);
    }
}
