/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:31:58 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/16 14:16:21 by zouazrou         ###   ########.fr       */
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

	i = 0;
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
		garbage_collect(name, true);
		garbage_collect(value, true);
		var = ft_getvarenv(name);
		if (var)
			var->value = value;
		else
			add_var(get_addr_env(NULL), new_var(args[i]));
	}
	return (status);
}
/*
==224547== 8 bytes in 4 blocks are definitely lost in loss record 3 of 79
==224547==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==224547==    by 0x404E10: strdup_org (envp.c:23)
==224547==    by 0x404FF7: sep_name_value (envp.c:72)
==224547==    by 0x4050A9: new_var (envp.c:88)
==224547==    by 0x401748: ft_export (ft_export.c:66)
==224547==    by 0x404A84: exec_built_in (utils.c:100)
==224547==    by 0x40453A: exe_single_built_in (execution.c:183)
==224547==    by 0x405743: main (main.c:121)
*/
