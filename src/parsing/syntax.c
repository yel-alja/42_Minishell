/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:32:56 by yel-alja          #+#    #+#             */
/*   Updated: 2025/06/08 18:35:21 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int into_quote(char *input , int *i , char c)
{
    *i += 1;
    while(input[*i])
    {
        if(input[*i] == c)
            return 1;
        *i += 1;
    }
    return 0;
}

int check_quotes(char *input)
{
    int i = 0;

    while(input[i])
    {
        if(input[i] == '"')
        {
            if(!into_quote(input , &i , '"'))
            {
                write(2 , "unclosed double quotes\n" , 23);   
                return (0);
            }
        }
        else if (input[i] == '\'')
        {
              if(!into_quote(input , &i , '\''))
              {
                    write(2 , "unclosed single quotes\n" , 23);
                    return (0);
              }
        }
        i++;
    }
    return (1);
}

int check_syntax(t_token *token)
{
    if(!token)
        return (0);
    if(token->type == PIPE)
    {
        write(2 , "syntax error\n" ,13);
        return (0);   
    }
    while(token)
    {
        if((token->type == PIPE || is_operator(token)) 
                && token->next == NULL)
        {
             write(2 , "syntax error\n" ,13);
            return (0);   
        }
        if(is_operator(token) && is_operator(token->next))
        {
             write(2 , "syntax error\n" ,13);
            return (0);   
        }   
        token = token->next;
    }
    return (1);
}
