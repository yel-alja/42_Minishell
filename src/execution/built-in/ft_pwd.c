/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:05:30 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/19 23:59:56 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_pwd(char **args)
{
	char	*buffer;

	(void)args;
	buffer = NULL;
	buffer = getcwd(buffer, 0);
	if (!buffer)
		errmsg(NULL, "getcwd", NULL);
	garbage_collect(buffer, true);
	ft_putendl_fd(buffer, STDOUT_FILENO);
	return (0);
}
