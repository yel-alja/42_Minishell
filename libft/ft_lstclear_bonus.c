/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:04:01 by zouazrou          #+#    #+#             */
/*   Updated: 2024/11/03 17:04:03 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*previous;
	t_list	*current;

	if (!lst)
		return ;
	previous = *lst;
	current = *lst;
	while (previous)
	{
		current = current->next;
		ft_lstdelone(previous, del);
		previous = current;
	}
	*lst = NULL;
}
