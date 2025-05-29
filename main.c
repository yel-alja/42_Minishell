/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:27:14 by yel-alja          #+#    #+#             */
/*   Updated: 2025/05/29 22:04:25 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void print_tokens(t_token *token)
{
    while(token)
    {
        printf("{%s, %d}\n" , token->value, token->type);
        token = token->next;
    }
}

int main()
{
    while(1)
    {
        t_token *token ;
        char *input;
        input = readline("minishell> ");
        if(input)
            add_history(input);
        token = tokenizer(input);
        print_tokens(token);
        
    }
}