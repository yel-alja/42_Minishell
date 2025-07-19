/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:58:02 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/19 15:28:29 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*p;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	p = malloc((ft_strlen(s) + 1));
	garbage_collect(p, true);
	while (i < ft_strlen(s) + 1)
	{
		*(p + i) = s[i];
		i++;
	}
	return (p);
}
