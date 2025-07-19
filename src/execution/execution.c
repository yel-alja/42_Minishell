/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 23:12:37 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/19 15:46:05 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	wait_commands(t_cmd *cmd)
{
	int	*exit_status;

	exit_status = get_addr_exit_status(NULL);
	while (cmd)
	{
		if (cmd->pid)
			waitpid(cmd->pid, exit_status, 0);
		cmd = cmd->next;
	}
	process_exit_status();
}

void	exec_cmd(t_cmd *cmd)
{
	char	*vpath;
	char	**arr_env;

	if (cmd->error || !cmd->cmd)
		ft_clean(true, true, *get_addr_exit_status(NULL));
	vpath = ft_getenv("PATH");
	if ((is_path(cmd->cmd)) == true || !vpath || !*vpath)
		valid_path_executable(cmd);
	else if (!*cmd->cmd)
	{
		errmsg(NULL, cmd->cmd, "command not found");
		ft_clean(true, true, 127);
	}
	else
		search_in_path(cmd);
	arr_env = env_to_arr(*get_addr_env(NULL));
	execve(cmd->cmd, cmd->args, arr_env);
	errmsg("execve", cmd->args[0], NULL);
	ft_clean(true, true, EXIT_FAILURE);
}

void	exe_child_proc(t_cmd *cmd, int *fd)
{
	int	*exit_status;

	exit_status = get_addr_exit_status(NULL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (cmd->next)
	{
		ft_close(fd + 0);
		cmd->fd_output = fd[1];
	}
	if (!cmd->cmd)
		*exit_status = 0;
	if (open_redirects(cmd))
		ft_clean(true, true, *get_addr_exit_status(NULL));
	if (is_built_in(cmd) == true)
		exec_built_in(cmd);
	else
		exec_cmd(cmd);
	ft_clean(true, true, *get_addr_exit_status(NULL));
}

int	exec_simple_cmd(t_cmd *cmd)
{
	pid_t	pid;
	int		fd[2];

	if (cmd->next)
	{
		if (pipe(fd) == -1)
			return (errmsg(NULL, "pipe", NULL), 1);
		ft_close(&cmd->next->fd_input);
		cmd->next->fd_input = fd[0];
	}
	pid = fork();
	if (pid == -1)
		return (errmsg(NULL, "fork", NULL), 1);
	else if (pid)
	{
		if (cmd->next)
			ft_close(fd + 1);
		ft_close(&cmd->fd_input);
		ft_close(&cmd->fd_output);
		cmd->pid = pid;
	}
	else
		exe_child_proc(cmd, fd);
	return (0);
}

void	exe_pipeline_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		*status;

	if (!cmd)
		return ;
	tmp = cmd;
	status = get_addr_exit_status(NULL);
	while (tmp)
	{
		if (exec_simple_cmd(tmp))
		{
			*status = 1;
			return ;
		}
		tmp = tmp->next;
	}
	signal(SIGINT, SIG_IGN);
	wait_commands(cmd);
	signal(SIGINT, ctrl_c);
}
