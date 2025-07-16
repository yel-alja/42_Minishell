/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:56:26 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/16 11:59:28 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countnbr(int n)
{
	size_t	len;

	len = 0;
	if (n >= 0 && n <= 9)
		return (1);
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*p;
	size_t	lennb;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	lennb = ft_countnbr(n);
	p = malloc(lennb + 1);
	garbage_collect(p, true);
	if (n < 0)
	{
		p[0] = '-';
		n *= -1;
	}
	p[lennb] = '\0';
	while (n > 0)
	{
		p[--lennb] = n % 10 + 48;
		n /= 10;
	}
	return (p);
}
