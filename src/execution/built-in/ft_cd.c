/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd .c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:06:10 by zouazrou          #+#    #+#             */
/*   Updated: 2025/05/27 10:06:53 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// (X)
int cd(char **args)
{
    struct stat file;

    // check num of argms
    if (!args || !*args)

    // if arg 'cd' || 'cd ~' -> moving to $HOME env (check getenv())
    /*
        Handling this case
    */
    if (args[2] != NULL)
        return (errmsg("cd", NULL, "too many arguments"), 1);
    // check if exist
    if (access(args[1], F_OK))
        return (errmsg("cd", args[1],"No such file or directory"), 1);
    if (stat(args[1], &file))
        return (perror("stat"), 3);
    // check is dir
    // if (!S_ISDIR(file.st_mode))
    //     return (errmsg("cd: test_f: Not a directory\n"), 1);
    // check permission
    // if (access(args[1], X_OK))
    //     return (errmsg("cd: "), errmsg(args[1]), errmsg(": Permission denied\n"), 1);
    // moving to diroctory
    if (chdir(args[1]))
        return (errmsg("cd", args[1], NULL), 6);

	// update env var $PWD

    return (0);
}
