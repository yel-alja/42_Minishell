/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 09:03:59 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/19 15:48:21 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	check_sign_nega(char *num, int *index)
{
	if (num[*index] == '-')
		return ((*index)++, true);
	if (num[*index] == '+')
		return ((*index)++, false);
	return (false);
}
/*
[0] : error
[1] : valid
[2] : min long
*/

int	check_range(char *num, int *index, int c, bool nega)
{
	if (c == 19)
	{
		if (!ft_strcmp("9223372036854775808", num + (*index)) && nega == true)
			return (2);
		if (ft_strcmp("9223372036854775808", num + (*index)) > 0
			&& nega == true)
			return (0);
		if (ft_strcmp("9223372036854775807", num + (*index)) < 0)
			return (0);
	}
	return (1);
}

int	check_args(char *num, int *index)
{
	int		i;
	int		c;
	bool	nega;

	nega = check_sign_nega(num, index);
	while (num[*index] && num[*index] == '0')
		(*index)++;
	i = *index;
	c = 0;
	while (num[i])
	{
		if (!ft_isdigit(num[i++]))
			return (0);
		c++;
		if (c > 19)
			return (0);
	}
	return (check_range(num, index, c, nega));
}

int	ft_exit(char **args)
{
	int				i;
	int				ret_val;
	unsigned char	exit_status;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	exit_status = *get_addr_exit_status(NULL);
	if (!args[1])
		ft_clean(true, true, *get_addr_exit_status(NULL));
	i = 0;
	ret_val = check_args(args[1], &i);
	if (ret_val == 1 && args[2])
		return (errmsg(NULL, "exit", "too many arguments"), 1);
	exit_status = ft_atoi(args[1]);
	if (!ret_val)
	{
		errmsg(NULL, "exit", "numeric argument required");
		ft_clean(true, true, 2);
	}
	if (ret_val == 2)
		ft_clean(true, true, 0);
	ft_clean(true, true, exit_status);
	return (255);
}
