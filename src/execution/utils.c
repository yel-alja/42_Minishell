/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:36:51 by zouazrou          #+#    #+#             */
/*   Updated: 2025/05/27 12:03:25 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	errmsg(char *cmd, char *arg, char *err)
{
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(cmd, 2);
	}
	else
		ft_putstr_fd("shell", 2);
	if (arg)
	{
		ft_putchar_fd(' ', 2);
		ft_putstr_fd(arg, 2);
	}
	if (err)
	{
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(err, 2);
	}
	else
		perror("");
}
// shell: errmsg

// (X) ./a.out/
// This is only case : exe
t_bool	is_path(char *file)
{
	int	i;

	i = -1;
	while (file[++i])
	{
		if (file[i] == '/')
			return (TRUE);
	}
	return (FALSE);
}

t_bool	is_built_in(char *cmd)
{
    if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd")
    || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
    || !ft_strcmp(cmd, "exit"))
        return (1);
    return (0);
}
