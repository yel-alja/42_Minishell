/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 09:06:36 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/11 09:41:53 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int check_dollar(char *str)
{
    int i = 0;
    while(str[i])
    {
        if(str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
            return (1);
        i++;
    }
    return (0);
}

char *flag_splitters(char *value)
{
    int i = 0;
    char *res = malloc(ft_strlen(value) + 1); //garbage
    if(!value)
        return NULL;
    while(value[i])
    {
        if(value[i] == '\n' || value[i] == ' ' || value[i] == '\t')
            res[i] = 14;
        else
            res[i] = value[i];
        i++;
    }
    res[i] = '\0';
    return (res);
}

char *var(char *token , t_env *env , int flag)
{
    int i = 0;
    int start = 0;
    char *var_name= NULL;
    char *var_value = NULL;
    char *p = NULL;
    while(token[i])
    {
        if(token[i] == '$' && (ft_isalpha(token[i + 1]) || token[i + 1] == '_'))
        {
            i++;
            start = i;
            while(token[start] && (ft_isalnum(token[start]) || token[start] == '_') && !is_whitespace(token[start]) &&
                        token[start] != '$')
                start++;
            p = ft_substr(token , 0 , i - 1);
            garbage_collect(p , 0);
            var_name = ft_substr(token , i - 1, start - i + 1);
            garbage_collect(var_name , 0);
            var_value = getenv(var_name + 1); //?
            if(flag == 1)
            {
                var_value = flag_splitters(var_value);
            }
            p = ft_strjoin(p , var_value);
            garbage_collect(p , 0);
            p = ft_strjoin(p , token + start);
            garbage_collect(p , 0);
            token = p;
            i = -1;
        }
        i++;
    }
    return (p);
}

char *expansion(char *token ,t_env *env , int flag)
{
    char *res = NULL;
    if(!check_dollar(token))
        return token;
    res = var(token ,env ,flag);
    return res;
}
