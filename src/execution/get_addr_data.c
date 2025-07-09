/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_addr_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 09:04:08 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/09 08:27:49 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	*get_addr_exit_status(int *ptr)
{
	static int	*addr;

	if (addr == NULL)
		addr = ptr;
	return (addr);
}

t_env	**get_addr_env(t_env **ptr)
{
	static t_env	**addr;

	if (addr == NULL)
		addr = ptr;
	return (addr);
}

t_cmd	**get_addr_cmd(t_cmd **ptr)
{
	static t_cmd	**addr;

	if (addr == NULL)
		addr = ptr;
	return (addr);
}
