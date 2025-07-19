/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:05:30 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/19 14:17:28 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// (X)
int	ft_pwd(char **args)
{
	char	*buffer;

	(void)args;
	buffer = NULL;
	buffer = getcwd(buffer, 0);
	if (!buffer)
		return (errmsg("getcwd", NULL, NULL), errno);
	printf("%s\n", buffer);
	ft_putendl_fd(buffer, STDOUT_FILENO);
	return (0);
}
