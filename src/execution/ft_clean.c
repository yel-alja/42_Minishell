/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 08:55:19 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/19 14:43:58 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// if "status" was btw 0-255 then exit with code "status"
// otherwise doest exit
void	ft_clean(bool own_env, bool garbage, int status)
{
	if (own_env == true)
		free_env();
	if (garbage == true)
		garbage_collect(NULL, false);
	if (status >= 0 && status <= 255)
		exit(status);
}

void		process_exit_status(void)
{
	int	*exit_status;

	exit_status = get_addr_exit_status(NULL);
	if (WIFSIGNALED(*exit_status) && *exit_status == SIGQUIT + 128)
		errmsg(NULL, NULL, "Quit (core dumped)");
	if (WIFEXITED(*exit_status))
		*exit_status = WEXITSTATUS(*exit_status);
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

void	errmsg(char *cmd, char *arg, char *err)
{
	char	*str;
	// char	*str;

	str = NULL;
	if (cmd)
		str = ft_strjoin(str, cmd);
	else
		str = ft_strjoin(str, SH_NAME);
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
