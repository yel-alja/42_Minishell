/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:05:30 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/30 09:24:46 by yel-alja         ###   ########.fr       */
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
	garbage_collect(buffer, false);
	ft_putendl_fd(buffer, STDOUT_FILENO);
	return (0);
}
