/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:07:51 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/14 14:50:15 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	free_var(t_env *var)
{
	free(var->name);
	free(var->value);
	free(var);
}
void	remove_from_env(char *name_var)
{
	t_env	*var;
	t_env	**env;
	t_env	*tmp;

	env = get_addr_env(NULL);
	tmp = *env;
	if (!ft_strcmp((*env)->name, name_var))
	{
		var = *env;
		(*env) = (*env)->next;
		free_var(var);
		return ;
	}
	while (tmp)
	{
		if (tmp->next && !ft_strcmp(tmp->next->name, name_var))
		{
			var = tmp->next;
			tmp->next = tmp->next->next;
			free_var(var);
			return ;
		}
		tmp = tmp->next;
	}
}
int	ft_unset(char **args)
{
	int	i;

	i = 0;
	while (args[++i])
		remove_from_env(args[i]);
	return (0);
}
