/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 11:00:38 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/19 22:47:07 by zouazrou         ###   ########.fr       */
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

char	*ft_getenv(char *name)
{
	t_env	*env;

	if (!ft_strcmp(name, "?"))
		return (ft_itoa(*get_addr_exit_status(NULL)));
	env = *get_addr_env(NULL);
	while (env)
	{
		if (!ft_strcmp(name, env->name))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	printenv(t_env *e, bool d_x)
{
	char	*line;

	while (e)
	{
		line = NULL;
		if (d_x == true)
		{
			line = ft_strjoin(line, "declare -x ");
			line = ft_strjoin(line, e->name);
			line = ft_strjoin(line, "=\"");
			line = ft_strjoin(line, e->value);
			line = ft_strjoin(line, "\"");
		}
		else
		{
			line = ft_strjoin(line, e->name);
			line = ft_strjoin(line, "=");
			line = ft_strjoin(line, e->value);
		}
		ft_putendl_fd(line, STDOUT_FILENO);
		e = e->next;
	}
}
