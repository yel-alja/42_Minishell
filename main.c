/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:27:14 by yel-alja          #+#    #+#             */
/*   Updated: 2025/05/30 23:13:36 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char *type_to_str(t_type type)
{
    if (type == PIPE) return "PIPE";
    if (type == APPEND) return "APPEND";
    if (type == OUTPUT) return "REDIR_OUT";
    if (type == INPUT) return "REDIR_IN";
    if (type == HEREDOC) return "HEREDOC";
    return "WORD";
}

void print_tokens(t_token *token)
{
    while(token)
    {   
         printf("\033[36m[value : \033[0m\033[33m%s\033[0m\033[36m]    [type : \033[0m\033[32m%s\033[0m\033[36m]\033[0m\n",token->value, type_to_str(token->type));
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