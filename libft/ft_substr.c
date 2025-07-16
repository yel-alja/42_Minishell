/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 16:15:54 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/16 11:37:36 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*p;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	i = 0;
	p = malloc(len + 1);
	garbage_collect(p, true);
	while (i < len && s[start])
		p[i++] = s[start++];
	p[i] = '\0';
	return (p);
}
