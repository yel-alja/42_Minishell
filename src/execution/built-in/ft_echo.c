/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 10:19:40 by zouazrou          #+#    #+#             */
/*   Updated: 2025/05/27 09:25:25 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_bool	option_n(char *args)
{
	int	j;

	j = 0;
	if (!args || !args[0] || !args[1])
		return (FALSE);
	while (args[j])
	{
		if ((!j && args[j] != '-') || (j && args[j] != 'n'))
			return (FALSE);
		j++;
	}
	return (TRUE);
}

int	echo(char **args)
{
	int		i;
	t_bool	flag;

	i = 1;
	flag = FALSE;

	if (!args || !*args)
		return (1);

	flag = option_n(args[i]);
	if (flag == TRUE)
		i++;
    while (args[i])
    {
        if ((i != 1 && flag == FALSE) || (i != 2 && flag == TRUE))
            printf(" ");
        printf("%s", args[i++]);
    }
    if (flag == FALSE)
        printf("\n");
    return (0);
}
