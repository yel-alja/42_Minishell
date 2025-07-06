/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:36:51 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/05 17:57:55 by zouazrou         ###   ########.fr       */
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
		perror(" ");
}
// shell: errmsg

// (X) ./a.out/
// This is only case : exe
bool	is_path(char *file)
{
	int	i;

	i = -1;
	while (file[++i])
	{
		if (file[i] == '/')
			return (true);
	}
	return (false);
}

bool	search_in_path(t_cmd *cmd)
{
	int		p;
	char	*str;
	char	**paths;

	paths = ft_split(getenv("PATH"), ':');
	p = -1;
	while (paths[++p])
	{
		str = ft_strjoin(paths[p], "/");
		str = ft_strjoin(str, cmd->cmd);
		if (access(str, F_OK | X_OK) == 0)
		{
			cmd->cmd = str;
			return (true);
		}
	}
	return (false);
}

bool	is_built_in(char *cmd)
{
    // if (!ft_strcmp(cmd, "pwd"))
	// if (!ft_strcmp(cmd, "exit"))
	// if (!ft_strcmp(cmd, "cd"))
	// if (!ft_strcmp(cmd, "env"))
	// if (!ft_strcmp(cmd, "unset"))
	// if (!ft_strcmp(cmd, "echo"))
    //     return (1);
    return (0);
}

int ft_close(int *fd)
{
	if (!isatty(*fd))
		return (close(*fd));
	return (0);
}
