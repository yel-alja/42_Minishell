/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 09:06:36 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/16 14:07:50 by zouazrou         ###   ########.fr       */
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
	if(!value)
		return NULL;
    int i = 0;
    char *res = malloc(ft_strlen(value) + 1); //garbage
    garbage_collect(res, true);
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

char *var(char *token , int flag)
{
	token = ft_strdup(token);
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
            var_name = ft_substr(token , i - 1, start - i + 1);
            var_value = ft_getenv(var_name + 1); // SEGV : TEST CASE $DFG
            if(flag == 1)
            {
                var_value = flag_splitters(var_value);
            }
            p = ft_strjoin(p ,var_value);
            p = ft_strjoin(p ,token + start);
            token = p;
        }
        i++;
    }
    return p;
}


char *expansion(char *token , int flag)
{
    char *res = NULL;
    if(!check_dollar(token))
        return token;
    res = var(token  ,flag);
    return res;
}
