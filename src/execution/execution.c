/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 23:12:37 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/05 18:34:08 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

void	wait_commands(t_cmd *cmd, int *exit_status)
{
	while (cmd)
	{
		waitpid(cmd->pid, exit_status, 0);
		if (WIFSIGNALED(*exit_status))
			*exit_status += 128;
		cmd = cmd->next;
	}
}

void		executable(t_cmd *cmd, int *exit_status, t_env **env)
{
	if ((is_path(cmd->cmd)) == false)
	{
		if (search_in_path(cmd) == false)
		{
			errmsg(NULL, cmd->cmd, "command not found");
			exit(127);
		}
	}
	if (execve(cmd->cmd, cmd->args, NULL) == -1)
	{
		errmsg("execve", cmd->args[0], NULL);
		exit(EXIT_FAILURE);
	}
}

int		run_redircts(t_cmd *cmd, int *exit_status)
{
	// redirect input
	if (!isatty(cmd->fd_input))
	{
		dup2(cmd->fd_input, STDIN_FILENO);
	}
	ft_close(&cmd->fd_input);
	// redirect output
	if (!isatty(cmd->fd_output))
	{
		dup2(cmd->fd_output, STDOUT_FILENO);
	}
	ft_close(&cmd->fd_output);
	return (0);
}

void		run_cmd(t_cmd *cmd, int *exit_status, t_env **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		errmsg(NULL, "fork", NULL);
	if (!pid)
	{
		run_redircts(cmd, exit_status);
		if (is_built_in(cmd->cmd) == true)
			printf("mazal\n");
		else
			executable(cmd, exit_status, env);
	}
	else
	{
		ft_close(&cmd->fd_input);
		ft_close(&cmd->fd_output);
		cmd->pid = pid;
	}
}

void	open_redirects(t_cmd *cmd, int *exit_status, t_env **env)
{
	t_redir	*redir;

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
			break;
		}
		redir = redir->next;
	}
}

int	exe_cmd_line(t_cmd *cmd, int *exit_status, t_env **env)
{
	open_redirects(cmd, exit_status, env);
	run_cmd(cmd, exit_status, env);
	wait_commands(cmd, exit_status);
	printf("exit status : %d\n", *exit_status);
	return (0);
}

/*
< file1 cat << EOF < file2 	> appfile > outfile < file.log

"< file.log",  "cat", "> outfile"
fd-for-read {3}       fd-for-write {4}


*/

// int main(int argc, char const *argv[])
// {
// 	t_cmd	cmd;
// 	int	exit_status = 0;

// 	cmd.cmd = ft_strdup("/bin/cata");
// 	cmd.args = malloc(sizeof(char *) * 2);
// 	cmd.args[0] = ft_strdup("cat");
// 	cmd.args[1] = NULL;
// 	cmd.fd_input = STDIN_FILENO;
// 	cmd.fd_output = STDOUT_FILENO;
// 	cmd.error = false;
// 	cmd.redirects = new_red("file1", INPUT);
// 	// cmd.redirects->next = new_red("file.log", OUTPUT);
// 	cmd.redirects->next = new_red("app.log", INPUT);
// 	cmd.next = NULL;
// 	exe_cmd_line(&cmd, &exit_status, NULL);
// 	return 0;
// }

// cc  src/execution/built-in/*.o libft/*.o src/execution/*.c src/parsing/*.o -lreadline
