/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:31:58 by zouazrou          #+#    #+#             */
/*   Updated: 2025/05/27 12:11:14 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void print_env(t_env *env, char flage);

// return (0) if not a valid 'identifier'
// return (1) Valid and has 'value'
// return (2) Valid and doesn't have 'value'
int	check_valid_syntax(char *arg)
{
	int		i;
	t_bool	has_val;

	i = 0;
	has_val = FALSE;
	if (!arg || !arg[i])
		return (0);
	if (!isalpha(arg[i]) && arg[i] != '_')
		return (0);
	while (arg[++i])
	{
		if (arg[i] == '=')
			return (1);
		if ((!ft_isalnum(arg[i]) && arg[i] != '_'))
			return (0);
	}
	return (2);
}

int	export(char **args, t_env **env)
{
	t_env	*var;
	int		i;
	int		rtn_val;

	// if (word == TRUE) // then set the  value of that variable shall be set to word.
	// if (!args[1])
	// 	return (print_env(env, 'x'), 0);
	i = 0;
	while (args[++i])
	{
		rtn_val = check_valid_syntax(args[i]);
		if (rtn_val == 0)
			// errmsg("bash: export: not a valid identifier\n");
			errmsg("export", NULL, "not a valid identifier");
		// else if (rtn_val == 1)
		// 	insert_var(env);
		// else if (rtn_val == 2)
		// 	;
			return (0);
	}
	return (0);

}
