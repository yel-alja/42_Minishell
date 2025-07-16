/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:31:58 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/12 09:44:32 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// void print_env(t_env *env, char flage);

// return (0) if not a valid 'identifier'
// return (1) Valid and has 'value'
// return (2) Valid and doesn't have 'value'
bool	check_valid_syntax(char *arg)
{
	int		i;
	bool	has_val;

	i = 0;
	has_val = false;
	if (!arg || !arg[i])
		return (false);
	if (!isalpha(arg[i]) && arg[i] != '_')
		return (false);
	while (arg[++i])
	{
		if (arg[i] == '=')
			break;
		if ((!ft_isalnum(arg[i]) && arg[i] != '_'))
			return (false);
	}
	return (true);
}

int	ft_export(char **args)
{
	int		i;
	int		status;
	char	*name;
	char	*value;
	t_env	*var;

	status = 0;
	if (!args[1])
		return (printenv(*get_addr_env(NULL), true), status);
	i = 0;
	while (args[++i])
	{
		if (check_valid_syntax(args[i]) == false)
		{
			errmsg("export", NULL, "not a valid identifier");
			status = 1;
			continue;
		}
		sep_name_value(args[i], &name, &value);
		var = ft_getvarenv(name);
		if (var)
			var->value = value;
		else
			add_var(get_addr_env(NULL), new_var(args[i]));
	}
	return (status);
}
