/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:36:51 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/17 11:40:52 by zouazrou         ###   ########.fr       */
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
	if (arg)
	{
		str = ft_strjoin(str, ": ");
		str = ft_strjoin(str, arg);
	}
	str = ft_strjoin(str, ": ");
	if (err)
		str = ft_strjoin(str, err);
	else
		str = ft_strjoin(str, strerror(errno));
	str = ft_strjoin(str, "\n");
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

void	search_in_path(t_cmd *cmd)
{
	int		p;
	char	*str;
	int		flag;
	char	**paths;

	paths = ft_split(ft_getenv("PATH"), ':');
	// if (!paths)
	// 	exit(err)
	p = -1;
	flag = 0;
	while (paths[++p])
	{
		str = ft_strjoin(paths[p], "/");
		str = ft_strjoin(str, cmd->cmd);

		if (access(str, F_OK) == 0)
			flag = 1;
		if (access(str, F_OK | X_OK) == 0)
		{
			cmd->cmd = str;
			return ;
		}
	}
	if (flag == 0)
		exit((errmsg(NULL, cmd->cmd, "command not found"), garbage_collect(NULL, false), 127));
	else if (flag == 1)
		exit((errmsg(NULL, cmd->cmd, "Permission denied"), garbage_collect(NULL, false), 126));
}

int	exec_built_in(t_cmd *cmd)
{
	int	*status;

	status = get_addr_exit_status(NULL);
	if (!ft_strcmp(cmd->cmd, "pwd"))
		*status = ft_pwd(cmd->args);
	if (!ft_strcmp(cmd->cmd, "echo"))
		*status = ft_echo(cmd->args);
	if (!ft_strcmp(cmd->cmd, "cd"))
		*status = ft_cd(cmd->args);
	if (!ft_strcmp(cmd->cmd, "env"))
		*status = ft_env(cmd->args);
	if (!ft_strcmp(cmd->cmd, "export"))
		*status = ft_export(cmd->args);
	if (!ft_strcmp(cmd->cmd, "exit"))
		*status = ft_exit(cmd->args);
	if (!ft_strcmp(cmd->cmd, "unset"))
		*status = ft_unset(cmd->args);
    return (*status);
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

	if (*fd > -1 && !isatty(*fd))
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
	garbage_collect(arr, true);
	i = 0;
	while (env)
	{
		arr[i] = ft_strjoin(env->name, "=");
		arr[i] = ft_strjoin(arr[i], env->value);
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
