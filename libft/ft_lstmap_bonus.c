/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:04:12 by zouazrou          #+#    #+#             */
/*   Updated: 2024/11/03 17:04:13 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_head;
	t_list	*current;

	current = lst;
	new_head = NULL;
	while (current)
	{
		ft_lstadd_back(&new_head, ft_lstnew(f(current->content)));
		if (!new_head)
			del(new_head);
		current = current->next;
	}
	return (new_head);
}
