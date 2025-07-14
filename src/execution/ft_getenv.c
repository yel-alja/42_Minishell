/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:00:38 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/12 09:08:12 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *ft_getenv(char *name , t_env *env)
{
    while(env)
    {
        if(!ft_strcmp(name , env->name))
            return(env->value);
        env = env->next;    
    }
    return (NULL);
}