/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 09:27:11 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/06 11:06:57 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void expander(t_token **tk ,t_env *env)
{
    t_token *token = *tk;
    while(token)
    {
        if(check_dollar(token->value))
            token->value = expansion(token->value , env);
        token = token->next;    
    }
}