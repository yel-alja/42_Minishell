/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 09:03:59 by zouazrou          #+#    #+#             */
/*   Updated: 2025/05/27 12:11:52 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

// (X)
// code :128 Invalid argument to exit	ex: exit 3.14159
// exit takes only integer args in the range 0 - 255 (see first footnote)
int ft_exit(char **args)
{
	int	code;

	// if args)
	code = ft_atoi(args[1]);
	exit(code % 256);
}
