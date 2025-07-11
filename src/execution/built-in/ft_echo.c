/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:19:40 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/11 12:13:00 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
/*
echo -n -n

*/
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

	i = 1;
	flag = false;

	if (!args || !*args)
		return (1);

	flag = option_n(args[i]);
	if (flag == true)
		i++;
    while (args[i])
    {
        if ((i != 1 && flag == false) || (i != 2 && flag == true))
            printf(" ");
        printf("%s", args[i++]);
    }
    if (flag == false)
        printf("\n");
    return (0);
}
