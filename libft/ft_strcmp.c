/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:56:16 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/29 10:20:29 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while(*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}
