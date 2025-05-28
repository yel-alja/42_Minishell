/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:19:40 by zouazrou          #+#    #+#             */
/*   Updated: 2025/05/28 10:38:02 by yel-alja         ###   ########.fr       */
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

int	echo(char **args)
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
