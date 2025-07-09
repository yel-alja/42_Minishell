/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:31:58 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/09 11:25:02 by zouazrou         ###   ########.fr       */
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
	// t_env	*var;
	int		i;
	int		exit_status;
	t_env	*var;
	char	*tmp1;
	char	*tmp2;

	// if (word == true) // then set the  value of that variable shall be set to word.
	// if (!args[1])
	// 	return (print_env(env, 'x'), 0);
	exit_status = 0;
	if (!args[1])
		return (printenv(*get_addr_env(NULL), true), exit_status);
	i = 0;
	while (args[++i])
	{
		if (check_valid_syntax(args[i]) == false)
		{
			errmsg("export", NULL, "not a valid identifier");
			exit_status = 1;
			continue;
		}
		// if exist in env then update value
		sep_name_value(args[i], &tmp1, &tmp2);
		tmp1 = ft_getenv(tmp1, *get_addr_env(NULL));
		if (tmp1)
		{
			tmp1 = tmp2;
		}
		// else if not found in env
		else
		{
			var = new_var(args[i]);
			add_var(get_addr_env(NULL), var);
		}
	}
	return (exit_status);
}
/****-> C="xyz"
A="abc"

B="def"

C="jhi"


*/
