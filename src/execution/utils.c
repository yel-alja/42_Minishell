/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:36:51 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/19 15:39:29 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_size(t_env *tmp)
{
	int	len;

	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

char	**env_to_arr(t_env *env)
{
	int		i;
	int		len;
	char	**arr;

	if (env == NULL)
		return (NULL);
	len = env_size(env);
	arr = malloc((len + 1) * sizeof(char *));
	garbage_collect(arr, true);
	i = 0;
	while (env)
	{
		arr[i] = ft_strjoin(env->name, "=");
		arr[i] = ft_strjoin(arr[i], env->value);
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	*strdup_org(const char *s)
{
	char	*p;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	p = malloc((ft_strlen(s) + 1));
	if (!p)
		return (NULL);
	while (i < ft_strlen(s) + 1)
	{
		*(p + i) = s[i];
		i++;
	}
	return (p);
}
