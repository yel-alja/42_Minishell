/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 08:55:19 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/17 09:05:22 by zouazrou         ###   ########.fr       */
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
