/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:36:51 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/13 11:32:58 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	errmsg(char *cmd, char *arg, char *err)
{
	char	*str;
	// char	*str;

	str = NULL;
	if (cmd)
		str = ft_strjoin(str, cmd);
	else
		str = ft_strjoin(str, "shell");
	garbage_collect(str, 0);
	if (arg)
	{
		str = ft_strjoin(str, ": ");
		str = ft_strjoin(str, arg);
		garbage_collect(str, 0);
	}
	if (err)
	{
		str = ft_strjoin(str, ": ");
		str = ft_strjoin(str, err);
	}
	else
		str = ft_strjoin(str, strerror(errno));
	garbage_collect(str, 0);
	str = ft_strjoin(str, "\n");
	garbage_collect(str, 0);
	ft_putstr_fd(str, 2);
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

int	exec_built_in(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->cmd, "pwd"))
		return (ft_pwd(cmd->args));
	if (!ft_strcmp(cmd->cmd, "echo"))
		return (ft_echo(cmd->args));
	if (!ft_strcmp(cmd->cmd, "cd"))
		return (ft_cd(cmd->args));
	if (!ft_strcmp(cmd->cmd, "env"))
		return (ft_env(cmd->args));
	if (!ft_strcmp(cmd->cmd, "export"))
		return (ft_export(cmd->args));
	if (!ft_strcmp(cmd->cmd, "exit "))
		return (ft_exit(cmd->args));
	if (!ft_strcmp(cmd->cmd, "unset"))
		return (printf("mazal\n"));
    return (0);
}

bool	is_built_in(t_cmd *cmd)
{
    if (!ft_strcmp(cmd->cmd, "pwd"))
		return (true);
	if (!ft_strcmp(cmd->cmd, "echo"))
		return (true);
	if (!ft_strcmp(cmd->cmd, "cd"))
		return (true);
	if (!ft_strcmp(cmd->cmd, "env"))
		return (true);
	if (!ft_strcmp(cmd->cmd, "export"))
		return (true);
	if (!ft_strcmp(cmd->cmd, "exit"))
		return (true);
	if (!ft_strcmp(cmd->cmd, "unset"))
		return (true);
    return (false);
}
int ft_close(int *fd)
{
	int	r;

	if (!isatty(*fd))
	{
		r = close(*fd);
		*fd = -42;
		return (r);
	}
	return (0);
}

char **env_to_arr(t_env *env)
{
	int	i;
	int	len;
	char	**arr;
	t_env	*tmp;

	if (env == NULL)
		return (NULL);
	len = 0;
	tmp = env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	arr = malloc((len + 1) * sizeof(char *));
	if (!arr)
		return (perror("malloc"), NULL);
	i = 0;
	while (env)
	{
		arr[i] = ft_strjoin(env->name, "=");
		// garbage_collect(arr[i], 1)
		arr[i] = ft_strjoin(arr[i], env->value);
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
