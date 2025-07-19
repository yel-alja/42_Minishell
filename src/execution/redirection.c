/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:25:24 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/19 08:39:17 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	rd_input(char *file, int fd)
{
	ft_close(&fd);
	if (!file)
		return (errmsg(NULL, "red", "Filename Not Found"), -1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		errmsg(NULL, file, NULL);
	return (fd);
}

// If the file does not exist, it shall be created
// otherwise, it shall be truncated to be an empty file after being opened.
int	rd_output(char *file, int fd, t_type flag)
{
	ft_close(&fd);
	if (!file)
		return (errmsg(NULL, "red", "Filename Not Found"), -1);
	if (flag == APPEND)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0664);
	if (flag == OUTPUT)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd == -1)
		errmsg(NULL, file, NULL);
	return (fd);
}

void	redirct_fd(t_cmd *cmd)
{
	// (void)exit_status;
	// redirect input
	if (cmd->fd_input > -1)
		dup2(cmd->fd_input, STDIN_FILENO);
	ft_close(&cmd->fd_input);
	// redirect output
	if (cmd->fd_output > -1)
		dup2(cmd->fd_output, STDOUT_FILENO);
	ft_close(&cmd->fd_output);
}

int	open_redirects(t_cmd *cmd)
{
	int		*exit_status;

	exit_status = get_addr_exit_status(NULL);
	while (cmd->redirects)
	{
		if (cmd->redirects->type == HEREDOC || cmd->redirects->type == INPUT)
			cmd->fd_input = rd_input(cmd->redirects->filename, cmd->fd_input);
		else if (cmd->redirects->type == OUTPUT || cmd->redirects->type == APPEND)
			cmd->fd_output = rd_output(cmd->redirects->filename, cmd->fd_output, cmd->redirects->type);
		// Check if Error occured
		if (cmd->fd_input == -1 || cmd->fd_output == -1 || cmd->redirects->type == AMBG)
		{
			ft_close(&cmd->fd_input);
			ft_close(&cmd->fd_output);
			cmd->error = true;
			*exit_status = 1;
			if (cmd->redirects->type == AMBG)
				errmsg(NULL, NULL, "ambiguous redirect");
			return (1);
		}
		cmd->redirects = cmd->redirects->next;
	}
	redirct_fd(cmd);
	return (0);
}
