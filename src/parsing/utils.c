/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 09:18:00 by yel-alja          #+#    #+#             */
/*   Updated: 2025/05/29 18:23:07 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


char *ft_strndup(char *str , int size)
{
    char *p ;
    int i;
    
    p = malloc(size + 1); 
    garbage_collect(p);
    i = 0;
    while(i < size)
    {
        p[i] = str[i];
        i++;
    }
    p[i] = '\0';
    return (p);
}

int is_whitespace(char c)
{
    if((c == ' ' || (c >= 9 && c <= 13)))
        return (1);
    return (0);
}