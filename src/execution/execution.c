/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 23:12:37 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/16 11:16:25 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

bool	is_directory(char *path)
{
    struct stat stats;

    if (stat(path, &stats) == 0 && S_ISDIR(stats.st_mode))
        return (true);
    return (false);
}

void		process_exit_status(void)
{
	int	*exit_status;

	exit_status = get_addr_exit_status(NULL);
	if (WIFSIGNALED(*exit_status))
		*exit_status = *exit_status;
	else if (WIFEXITED(*exit_status))
		*exit_status = WEXITSTATUS(*exit_status);
}

void	wait_commands(t_cmd *cmd)
{
	int	*exit_status;

	exit_status = get_addr_exit_status(NULL);
	while (cmd)
	{
		waitpid(cmd->pid, exit_status, 0);
		process_exit_status();
		cmd = cmd->next;
	}
}

void	exec_cmd(t_cmd *cmd)
{
	char	*vpath;

	vpath = ft_getenv("PATH");
	if ((is_path(cmd->cmd)) == true || !vpath || !*vpath)
	{
		if (is_directory(cmd->cmd) == true)
			exit((errmsg(NULL, cmd->cmd, "Is a directory"), 126));
		if (!access(cmd->cmd, F_OK) && access(cmd->cmd, X_OK))
			exit((errmsg(NULL, cmd->cmd, NULL), 126));
		if (access(cmd->cmd, F_OK | X_OK))
			exit((errmsg(NULL, cmd->cmd, NULL), 127));
	}
	else
		search_in_path(cmd);
	execve(cmd->cmd, cmd->args, env_to_arr(*get_addr_env(NULL)));
	errmsg("execve", cmd->args[0], NULL);
	exit(EXIT_FAILURE);
}

void		run_redircts(t_cmd *cmd)
{
	// (void)exit_status;
	// redirect input
	if (!isatty(cmd->fd_input))
		dup2(cmd->fd_input, STDIN_FILENO);
	ft_close(&cmd->fd_input);
	// redirect output
	if (!isatty(cmd->fd_output))
		dup2(cmd->fd_output, STDOUT_FILENO);
	ft_close(&cmd->fd_output);
}

int	open_redirects(t_cmd *cmd)
{
	t_redir	*redir;
	int		*exit_status;

	exit_status = get_addr_exit_status(NULL);
	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == HEREDOC || redir->type == INPUT)
			cmd->fd_input = rd_input(redir->filename, cmd->fd_input);
		if (redir->type == OUTPUT || redir->type == APPEND)
			cmd->fd_output = rd_output(redir->filename, cmd->fd_output, redir->type);
		// Check if Error occured
		if (cmd->fd_input == -1 || cmd->fd_output == -1)
		{
			ft_close(&cmd->fd_input);
			ft_close(&cmd->fd_output);
			cmd->error = true;
			*exit_status = 1;
			return (1);
		}
		redir = redir->next;
	}
	run_redircts(cmd);
	return (0);
}

void		exec_simple_cmd(t_cmd *cmd) // IM HERE >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
{
	pid_t	pid;
	int		fd[2];

	if (cmd->next)
	{
		if (pipe(fd) == -1)
			return (errmsg(NULL, "pipe", NULL));
		ft_close(&cmd->next->fd_input);
		cmd->next->fd_input = fd[0];
	}
	pid = fork();
	if (pid == -1)
		errmsg(NULL, "fork", NULL);
	if (pid) // Parent proc
	{
		if (cmd->next)
		{
			ft_close(fd + 1);
		}
		ft_close(&cmd->fd_input);
		ft_close(&cmd->fd_output);
		cmd->pid = pid;
	}
	else  // Child proc
	{
		signal(SIGQUIT, SIG_DFL);
		if (cmd->next)
		{
			ft_close(fd + 0);
			cmd->fd_output = fd[1];
		}
		// if (run_pipe(fd[1]))
		// 	return ;
		if (open_redirects(cmd))
			return ;
		if (is_built_in(cmd) == true)
			exit(exec_built_in(cmd));
		else
			exec_cmd(cmd);
	}
}

int	exe_pipeline_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		exec_simple_cmd(tmp);
		tmp = tmp->next;
	}
	wait_commands(cmd);
	return (0);
}

int	exe_single_built_in(t_cmd *cmd)
{
	int	ttyin;
	int	ttyout;
	int	*exit_status;

	/***********built-in************/
	exit_status = get_addr_exit_status(NULL);
	ttyin = dup(STDIN_FILENO);
	ttyout = dup(STDOUT_FILENO);
	if (!open_redirects(cmd))
		*exit_status = exec_built_in(cmd);
	// call built-in function
	dup2(ttyin, STDIN_FILENO);
	dup2(ttyout, STDOUT_FILENO);
	close(ttyin);
	close(ttyout);
	return (0);
}
/*
< file1 cat << EOF < file2 	> appfile > outfile < file.log

"< file.log",  "cat", "> outfile"
fd-for-read {3}       fd-for-write {4}


*/
