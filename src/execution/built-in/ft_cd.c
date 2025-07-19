/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:06:10 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/19 15:32:06 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	update_env(char *curr_dir)
{
	t_env	*pwd;
	t_env	*oldpwd;

	pwd = ft_getvarenv("PWD");
	oldpwd = ft_getvarenv("OLDPWD");
	if (oldpwd && pwd)
	{
		free(oldpwd->value);
		oldpwd->value = pwd->value;
	}
	if (pwd)
	{
		if (!oldpwd)
			free(pwd->value);
		pwd->value = ft_strdup(curr_dir);
	}
}

int ft_cd(char **args)
{
	char	*path;

	path = args[1];
	if (!args[1])
	{
		path = ft_getenv("HOME");
		printf("=======%s\n" , path);
		if (!path)
			return (errmsg("yzsh: cd", path, "HOME not set"), EXIT_FAILURE);
		if (!*path)
			return (EXIT_SUCCESS);
	}
    else if (args[2])
        return (errmsg(NULL, "yzsh: cd", "too many arguments"), EXIT_FAILURE);

    if (chdir(path))
        return (errmsg("yzsh: cd", path, NULL), EXIT_FAILURE);
	// else
	// 	update_env(path);
    return (EXIT_SUCCESS);
}
