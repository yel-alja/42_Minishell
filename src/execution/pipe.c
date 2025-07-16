/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 08:28:29 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/07 11:11:53 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_pipe(t_cmd *cmd)
{
	int	fds[2];

	while (cmd)
	{
		// check if there are another command
		if (cmd->next == NULL)
			break;
		// check error happind
		if (pipe(fds) == -1)
		{
			/* close and free all memory */;
			perror("pipe");
			return (EXIT_FAILURE);
		}
		cmd->fd_output = fds[1];
		cmd->next->fd_input = fds[0];
		cmd = cmd->next;
	}
	return (0);
}
