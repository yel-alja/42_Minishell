/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 09:06:36 by yel-alja          #+#    #+#             */
/*   Updated: 2025/06/09 22:06:12 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int check_dollar(char *str)
{
    int i = 0;
    while(str[i])
    {
        if(str[i] == '$')
            return (1);
        i++;
    }
    return (0);
}
void search_and_replace(char *tkn , char *var_name, char *var_val , int nalen)
{
    int i= 0;
    int j;
    int len = ft_strlen(tkn) + ft_strlen(var_val) - nalen;
    char *res = malloc(len + 1);
    while(tkn[i])
    {
        if(!ft_strncmp(&tkn[i] , var_name , nalen)) 
        {
            j = 0;
            while(var_val[j])
            {
                res[i] =  var_val[j];
                i++;
                j++;
            }
        }
        else
        {
            res[i] = tkn[i];
        }
        i++;
    }
    res[i] = '\0';  
    printf("%s\n" , res);
}
void var(t_token *token)
{
    int i = 0;
    int start = 0;
    char *var_name= NULL;
    char *var_value = NULL;
    if(!check_dollar(token->value))
        return;
    while(token->value[i])
    {
        if(token->value[i] == '$')
        {
            i++;
            start = i;
            while(token->value[start] && !is_whitespace(token->value[start]) &&
                        token->value[start] != '$')
                start++;
            var_name = ft_substr(token->value , i, start - i + 1); //? garbage collect also for strdup bellow
            var_value = ft_strdup(getenv(var_name));                        //we should implement our getenv
            if(!var_value)
                continue;
            search_and_replace(token->value , var_name , var_value ,ft_strlen(var_name));
        }
        i++;
    }
}

void expansion(t_token **token)
{
    t_token *tmp;

    tmp = *token;
    
    while(tmp)
    {
        if(tmp->type == WORD && tmp->quote != 2)
        {
            var(tmp);
        }
        tmp = tmp->next;
    }
}
