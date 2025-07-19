/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:06:10 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/20 00:01:55 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_cd(char **args)
{
	char	*path;

	path = args[1];
	if (!args[1])
	{
		path = ft_getenv("HOME");
		if (!path)
			return (errmsg("yzsh: cd", path, "HOME not set"), EXIT_FAILURE);
		if (!*path)
			return (EXIT_SUCCESS);
	}
	else if (args[2])
		return (errmsg(NULL, "yzsh: cd", "too many arguments"), EXIT_FAILURE);
	if (chdir(path))
		return (errmsg("yzsh: cd", path, NULL), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
