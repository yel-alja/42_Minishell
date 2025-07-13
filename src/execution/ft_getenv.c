/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:00:38 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/13 10:58:33 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*ft_getvarenv(char *name)
{
	t_env	*env;

	env = *get_addr_env(NULL);
	while (env)
	{
		if (!ft_strcmp(name, env->name))
			return (env);
		env = env->next;
	}
	return (NULL);
}

char *ft_getenv(char *name)
{
	char	*str;
	t_env	*env;

	if (!ft_strcmp(name, "?"))
	{
		str = ft_itoa(*get_addr_exit_status(NULL));
		return (str);
	}
	env = *get_addr_env(NULL);
    while(env)
    {
        if(!ft_strcmp(name , env->name))
            return (env->value);
        env = env->next;
    }
    return (NULL);
}
