/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 23:12:37 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/04 17:43:42 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

void	child_process(t_cmd *cmd)
{
	(void)cmd; //?
	// rd_input(cmd);
	// return (1);
}

int		run_cmd(t_cmd *cmd)
{
	// int		fds[2];
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		errmsg(NULL, "fork", NULL);
	if (!pid) // Child Process
		child_process(cmd);

	return (9);
}
void	run_pipe(t_cmd *cmd, t_env **env)
{
	(void)cmd; //?
	(void)env; //?
	// while (cmd)
	// {
	// 	if (cmd->pipe)
	// }

}

void	run_redirects(t_cmd *cmd, t_env **env)
{
	t_redir	*redir;
	(void)env; //?
	redir = cmd->redirects;
	while (redir)
	{
		// if (redir->type == HEREDOC_Q || redir->type == HEREDOC)
		// 	cmd->fd_input = here_doc(redir->filename, cmd->fd_input);
		if (redir->type == INPUT)
			cmd->fd_input = rd_input(redir->filename, cmd->fd_input);
		else if (redir->type == OUTPUT)
			cmd->fd_output = rd_output(redir->filename, cmd->fd_output);
		else if (redir->type == APPEND)
			cmd->fd_output = rd_append(redir->filename, cmd->fd_input);
		// Check if Error occured
		if (cmd->fd_input == -1 || cmd->fd_input == -1)
			cmd->error = true;
		redir = redir->next;
	}
}

int	ft_execute(t_cmd *cmd, t_env **env)
{
	run_redirects(cmd, env);
	// run_pipe(cmd, env); // if I/O is a tty Otherwise Nothing happind.
	run_cmd(cmd);
	return (0);
}

/*
< file1 cat << EOF < file2 	> appfile > outfile < file.log

"< file.log",  "cat", "> outfile"
fd-for-read {3}       fd-for-write {4}


*/
