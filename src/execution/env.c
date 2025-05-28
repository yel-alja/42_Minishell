/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:49:53 by yel-alja          #+#    #+#             */
/*   Updated: 2025/05/28 10:22:29 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./../include/minishell.h"

t_env *lst_env(char *var)
{
	char **res;
	
	t_env *head ;
	head = malloc(sizeof(t_env));
	if(!head)
		return (NULL);
	if(ft_strncmp(var , "LS_COLORS" , 9) == 0)
	{
		head->name =  ft_strdup("LS_COLORS");
		head->value = ft_strdup(ft_strchr(var , '='));
	}
	else
	{
		res = ft_split(var , '=');
		head->name = ft_strdup(res[0]);
		head->value = ft_strdup(res[1]);
		head->next = NULL;
		free_s(res);
	}
	return(head);
}
t_env *do_env(char **env)
{
	int i = 0;
	t_env *head = NULL;
	t_env *tmp = NULL;
	while(env[i])
	{
		if(head == NULL)
			head = lst_new(env[i]);
		else
		{
			tmp = head;
			while(tmp->next)
				tmp = tmp->next;
			tmp->next = lst_new(env[i]);
		}
		i++;
	}
	return (head);
}