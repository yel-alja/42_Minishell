/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:19:40 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/19 14:15:54 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	option_n(char *args)
{
	int	j;

	j = 0;
	if (!args || !args[0] || !args[1])
		return (false);
	while (args[j])
	{
		if ((!j && args[j] != '-') || (j && args[j] != 'n'))
			return (false);
		j++;
	}
	return (true);
}

int	ft_echo(char **args)
{
	int		i;
	bool	flag;
	char	*str;

	i = 1;
	flag = false;
	str = NULL;
	if (!args || !*args)
		return (1);
	while (option_n(args[i]))
	{
		flag = true;
		i++;
	}
	while (args[i])
	{
		str = ft_strjoin(str, args[i]);
		if (args[++i])
			str = ft_strjoin(str, " ");
	}
	if (flag == false)
		str = ft_strjoin(str, "\n");
	ft_putstr_fd(str, STDOUT_FILENO);
	return (0);
}
