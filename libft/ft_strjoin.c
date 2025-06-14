/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:57:15 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/13 02:03:55 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_len(char const *s1, char const *s2, size_t *lens1, size_t *lens2)
{
	*lens1 = ft_strlen(s1);
	*lens2 = ft_strlen(s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	lens1;
	size_t	lens2;
	char	*p;

	ft_len(s1, s2, &lens1, &lens2);
	p = malloc(lens1 + lens2 + 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (i < lens1)
	{
		p[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < lens2)
	{
		p[i + lens1] = s2[i];
		i++;
	}
	p[i + lens1] = '\0';
	return (p);
}
