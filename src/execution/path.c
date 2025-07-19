/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 14:44:43 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/19 15:46:50 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_directory(char *path)
{
	struct stat	stats;

	if (stat(path, &stats) == 0 && S_ISDIR(stats.st_mode))
		return (true);
	return (false);
}

void	valid_path_executable(t_cmd *cmd)
{
	if (is_directory(cmd->cmd) == true)
	{
		errmsg(NULL, cmd->cmd, "Is a directory");
		ft_clean(1, 1, 126);
	}
	if (!access(cmd->cmd, F_OK) && access(cmd->cmd, X_OK))
	{
		errmsg(NULL, cmd->cmd, NULL);
		ft_clean(1, 1, 126);
	}
	if (access(cmd->cmd, F_OK | X_OK))
	{
		errmsg(NULL, cmd->cmd, NULL);
		ft_clean(1, 1, 127);
	}
}

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

void	check_flags(t_cmd *cmd, int flag)
{
	if (flag == 0)
	{
		errmsg(NULL, cmd->cmd, "command not found");
		ft_clean(true, true, 127);
	}
	else if (flag == 1)
	{
		errmsg(NULL, cmd->cmd, "Permission denied");
		ft_clean(true, true, 126);
	}
}

void	search_in_path(t_cmd *cmd)
{
	int		p;
	int		flag;
	char	**paths;
	char	*path_cmd;

	paths = ft_split(ft_getenv("PATH"), ':');
	// handle this
	if (!paths)
		exit(1);
	p = -1;
	flag = 0;
	while (paths[++p])
	{
		path_cmd = ft_strjoin(paths[p], "/");
		path_cmd = ft_strjoin(path_cmd, cmd->cmd);
		if (!access(path_cmd, F_OK))
			flag = 1;
		if (!access(path_cmd, F_OK | X_OK) && !is_directory(path_cmd))
		{
			cmd->cmd = path_cmd;
			return ;
		}
	}
	check_flags(cmd, flag);
}
