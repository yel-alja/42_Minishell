/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:17:00 by yel-alja          #+#    #+#             */
/*   Updated: 2025/05/28 18:02:42 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


t_token *lst_new(char *input , t_type type)
{
     t_token *node;
      
     node = malloc(sizeof(t_token));
     if(!node)
        garbage_collect(NULL);
    garbage_collect(node);
    node->value = ft_strdup(input);
    if(!node->value)
        garbage_collect(NULL);
    garbage_collect(node->value);
    node->type = type;
    node->next = NULL;
    return (node);
}
void lst_addback(t_token **head, t_token *node)
{
    t_token *tmp;
    
    if(*head == NULL)
        *head = node;
    else
    {
        tmp = *head;
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = node;
    }   
}

void check_red(char *input , int i , t_token **cmnd)
{
    t_token *command = NULL;
    
    if(input[i] == '|')
    {
        command = lst_new("|" , PIPE);
        lst_addback(cmnd , command);
        i++;    
    }
    // else if(input[i] )

}

t_token *tokenizer(char *input)
{
    t_token *cmnd = NULL;
    int i = 0;
    char **res;
    while(input[i])
    {
        while(input[i] && input[i] == ' ')
            i++;
        check_red(input , i ,&cmnd);
            
    }
    return NULL; //? should i do somthing here
}
