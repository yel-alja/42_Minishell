/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:31:58 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/19 15:49:21 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// return (0) Valid and has 'value'
// return (1) Valid and doesn't have 'value'
// return (2) if not a valid 'identifier'
int	check_valid_syntax(char *arg)
{
	int	i;

	i = 0;
	if (!arg || !arg[i])
		return (2);
	if (!isalpha(arg[i]) && arg[i] != '_')
		return (2);
	while (arg[++i])
	{
		if (arg[i] == '=')
			return (0);
		if ((!ft_isalnum(arg[i]) && arg[i] != '_'))
			return (2);
	}
	return (1);
}

int	ft_export(char **args)
{
	int	i;
	int	rt;
	int	status;

	status = 0;
	if (!args[1])
		return (printenv(*get_addr_env(NULL), true), status);
	i = 0;
	while (args[++i])
	{
		rt = check_valid_syntax(args[i]);
		if (rt == 0)
			add_var(new_var(args[i]));
		if (rt == 1)
			continue ;
		if (rt == 2)
		{
			errmsg("export", NULL, "not a valid identifier");
			status = 1;
		}
	}
	return (status);
}
