/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:49:53 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/02 09:24:24 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	sep_name_value(char *var, char **name, char **value)
{
	int		i;
	int		len;

	len = ft_charlen(var, "=");
	*name = malloc((len + 1) * sizeof(char));
	if (!*name)
		return (1);

	i = 0;
	while (i < len)
	{
		(*name)[i] = var[i];
		i++;
	}
	(*name)[len] = '\0';
	// var has no value
	if (var[len] == '\0')
		return (0);
	// var has value
	len++;
	*value = ft_strdup(var + len);
	return (0);
}

t_env	*new_var(char *var)
{
	t_env *node;

	node = malloc(sizeof(t_env));
	if(!node)
		return (NULL);
	node->name = NULL;
	node->value = NULL;
	node->next = NULL;
	sep_name_value(var, &node->name, &node->value);
	return(node);
}

void	add_var(t_env **head, t_env *var)
{
	var->next = *head;
	*head = var;
}

t_env	*get_envp(char **env)
{
	int		i;
	t_env	*head;

	i = -1;
	head = NULL;
	while(env[++i])
	{
		// printf("%s\n", env[i]);
		add_var(&head, new_var(env[i]));
		// printf("%s", head->name);
		// if (head->value)
		// {
			// printf("=");
			// printf("%s", head->value);
		// }
		// printf("\n");
	}
	// printf("\nsize %d\n", i);
	return (head);
}
