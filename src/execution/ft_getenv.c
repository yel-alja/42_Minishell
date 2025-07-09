/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:00:38 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/08 10:17:22 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *ft_getenv(char *name , t_env *env)
{
    while(env)
    {
        if(!ft_strncmp(name , env->name , ft_strlen(name)))
            return(env->value);
        env = env->next;
    }
    return (NULL);
}
