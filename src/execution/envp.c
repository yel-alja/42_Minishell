/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:49:53 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/20 00:21:46 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_env(void)
{
	t_env	*tmp;
	t_env	**env;

	env = get_addr_env(NULL);
	while (*env)
	{
		tmp = *env;
		*env = (*env)->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
	*env = NULL;
}

void	sep_name_value(char *var, char **name, char **value)
{
	int	i;
	int	len;

	len = ft_charlen(var, "=");
	*name = malloc((len + 1) * sizeof(char));
	if (!*name)
		ft_clean(true, true, EXIT_FAILURE);
	i = 0;
	while (i < len)
	{
		(*name)[i] = var[i];
		i++;
	}
	(*name)[len] = '\0';
	len++;
	if (value)
	{
		*value = strdup_org(var + len);
		if (!*value)
		{
			free(*name);
			ft_clean(true, true, EXIT_FAILURE);
		}
	}
}

t_env	*new_var(char *var)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = NULL;
	node->value = NULL;
	node->next = NULL;
	sep_name_value(var, &node->name, &node->value);
	ft_unset((char *[]){"unset", node->name, NULL});
	return (node);
}

void	add_var(t_env *var)
{
	t_env	*tmp;
	t_env	**head;

	if (!var)
		return ;
	head = get_addr_env(NULL);
	if (*head == NULL)
		*head = var;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = var;
	}
}

t_env	*get_envp(char **env)
{
	int		i;
	t_env	*tmp_var;

	i = -1;
	while (env[++i])
	{
		tmp_var = new_var(env[i]);
		if (!tmp_var)
		{
			ft_clean(true, true, EXIT_FAILURE);
		}
		add_var(tmp_var);
	}
	return (*get_addr_env(NULL));
}
