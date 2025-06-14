/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 09:06:36 by yel-alja          #+#    #+#             */
/*   Updated: 2025/06/14 10:41:31 by yel-alja         ###   ########.fr       */
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

char *remove_name(char *str ,char *str_rm)
{
    int i = 0;
    int j = 0;
    char *res = malloc(ft_strlen(str) - ft_strlen(str_rm) + 1);
    while(str[i])
    {
        if(!ft_strncmp(&str[i] , str_rm , ft_strlen(str_rm)))
        {
            i += ft_strlen(str_rm);
        }
        res[j] = str[i];
        j++;
        i++;
    }
    res[j] = '\0';
    return (res);
}

char *search_and_replace(char **token , char *var_name, char *var_val , int nalen)
{
    int i= 0;
    int j;
    char *tkn = (*token);
    int len = ft_strlen(tkn) + ft_strlen(var_val) - nalen + 1;
    char *res = malloc(len + 1);
    // garbage_collect(res);
    while(i < len)
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
    *token = remove_name(tkn , var_name);
    return res;
}

char *var(t_token *token)
{
    int i = 0;
    int start = 0;
    char *var_name= NULL;
    char *var_value = NULL;
    char *p = NULL;
    if(!check_dollar(token->value))
        return NULL;
    while(token->value[i])
    {
        if(token->value[i] == '$')
        {
            i++;
            start = i;
            while(token->value[start] && !is_whitespace(token->value[start]) &&
                        token->value[start] != '$')
                start++;
            var_name = ft_substr(token->value , i - 1, start - i + 1); //? garbage collect also for strdup bellow
            // garbage_collect(var_name);
            var_value = getenv(var_name + 1);                        //we should implement our getenv
            if(!var_value)
                continue;
            p = ft_strjoin(p , search_and_replace(&token->value , var_name , var_value ,ft_strlen(var_name)));
            i = -1;
        }
        i++;
    }
    return (p);
}

void expansion(t_token **token)
{
    t_token *tmp;

    tmp = *token;
    char *res = NULL;
    while(tmp)
    {
        if(tmp->type == WORD && tmp->quote != 2)
        {
            res = var(tmp);
            if(res) 
                tmp->value = res; //? i lose adress here  but maybe the garbage know it
        }
        tmp = tmp->next;
    }
}
