/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 23:12:37 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/09 14:39:00 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

void		process_exit_status(void)
{
	int	*exit_status;

	exit_status = get_addr_exit_status(NULL);
	if (WIFSIGNALED(*exit_status))
		*exit_status = WTERMSIG(*exit_status);
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
	if ((is_path(cmd->cmd)) == true)
	{
		if (!access(cmd->cmd, F_OK) && access(cmd->cmd, X_OK))
			exit((errmsg(NULL, cmd->cmd, NULL), 126));
		if (access(cmd->cmd, F_OK | X_OK))
			exit((errmsg(NULL, cmd->cmd, NULL), 127));
	}
	else if (search_in_path(cmd) == false)
		exit((errmsg(NULL, cmd->cmd, "command not found"), 127));
	execve(cmd->cmd, cmd->args, env_to_arr(*get_addr_env(NULL)));
	errmsg("execve", cmd->args[0], NULL);
	exit(EXIT_FAILURE);
}

void		run_redircts(t_cmd *cmd)
{
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
	*exit_status = 0;
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

	pid = fork();
	if (pid == -1)
		errmsg(NULL, "fork", NULL);
	if (pid) // Parent proc
	{
		ft_close(&cmd->fd_input);
		ft_close(&cmd->fd_output);
		cmd->pid = pid;
	}
	else  // Child proc
	{
		signal(SIGQUIT, SIG_DFL);
		if (open_redirects(cmd))
			return ;
		if (is_built_in(cmd) == true)
			exec_built_in(cmd);
		else
			exec_cmd(cmd);
	}
}


int	exe_pipeline_cmd(t_cmd *cmd)
{
	int	ttyin;
	int	ttyout;
	t_cmd	*tmp;

	ttyin = dup(STDIN_FILENO);
	ttyout = dup(STDOUT_FILENO);
	/***********Dup stdin & stdout**********/
	tmp = cmd;
	if (cmd->next)
		open_pipe(cmd);
	while (tmp)
	{
		exec_simple_cmd(tmp);
		tmp = tmp->next;
	}
	wait_commands(cmd);
	printf("[%d]\n", *get_addr_exit_status(NULL));
	/***********set Default fd************/
	dup2(ttyin, STDIN_FILENO);
	dup2(ttyout, STDOUT_FILENO);
	close(ttyin);
	close(ttyout);
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
