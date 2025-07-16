/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:49:53 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/16 09:03:57 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void free_env(t_env **env)
{
	t_env *tmp;

	while(*env)
	{
		tmp = *env;
		*env = (*env)->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

int	sep_name_value(char *var, char **name, char **value)
{
	int		i;
	int		len;

	len = ft_charlen(var, "=");
	*name = malloc((len + 1) * sizeof(char));
		if(!name)
			return (1);
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
		*value = ft_strdup(var + len); //malloc fail
	}
	return (0);
}

t_env	*new_var(char *var)
{
	t_env *node;

	node = malloc(sizeof(t_env)); // malloc fail
	if(!node)
		return (NULL);
	node->name = NULL;
	node->value = NULL;
	node->next = NULL;
	if(sep_name_value(var, &node->name, &node->value) == 1)
		return (NULL);
	return(node);
}

void	add_var(t_env **head, t_env *var)
{
	t_env *tmp;

	if (!var)
		return ;
	if(*head == NULL)
		*head = var;
	else
	{
		tmp = *head;
		while(tmp->next)
			tmp = tmp->next;
		tmp->next  = var;
	}
}

t_env	*get_envp(char **env)
{
	int		i;
	t_env	*head;
	t_env	*tmp;

	i = -1;
	head = NULL;
	while(env[++i])
	{
		tmp = new_var(env[i]);
		if(!tmp)
		{
			free_env(&head);
			exit(1);
		}
		add_var(&head, tmp);
	}
	return (head);
}
