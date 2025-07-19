/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 14:34:29 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/19 14:34:55 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	exec_built_in(t_cmd *cmd)
{
	int	*status;

	if (cmd->error)
		return (0);
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
	if (!cmd || !cmd->cmd)
		return (false);
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

void	exe_single_built_in(t_cmd *cmd)
{
	int	ttyin;
	int	ttyout;
	int	*exit_status;

	if (!cmd || cmd->error)
		return ;
	exit_status = get_addr_exit_status(NULL);
	if (!cmd->cmd)
		*exit_status = 0;
	ttyin = dup(STDIN_FILENO);
	ttyout = dup(STDOUT_FILENO);
	if (!open_redirects(cmd) && cmd->cmd)
	{
		if (!ft_strcmp(cmd->cmd, "exit"))
		{
			close(ttyin);
			close(ttyout);
		}
		*exit_status = exec_built_in(cmd);
	}
	dup2(ttyin, STDIN_FILENO);
	dup2(ttyout, STDOUT_FILENO);
	close(ttyin);
	close(ttyout);
}
