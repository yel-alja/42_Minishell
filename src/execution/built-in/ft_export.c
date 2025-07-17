/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:31:58 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/17 11:32:53 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// void print_env(t_env *env, char flage);

// return (0) Valid and has 'value'
// return (1) Valid and doesn't have 'value'
// return (2) if not a valid 'identifier'
int	check_valid_syntax(char *arg)
{
	int		i;

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
	int		i;
	int		rt;
	int		status;

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
			continue;
		if (rt == 2)
		{
			errmsg("export", NULL, "not a valid identifier");
			status = 1;
		}
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
