/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:58:02 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/09 21:24:47 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*p;
	size_t	i;

	i = 0;
	if (!s)
		return NULL;
	p = malloc((ft_strlen(s) + 1));
	if (p == NULL)
		return (p);
	while (i < ft_strlen(s) + 1)
	{
		*(p + i) = s[i];
		i++;
	}
	return (p);
}
