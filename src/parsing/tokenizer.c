/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:17:00 by yel-alja          #+#    #+#             */
/*   Updated: 2025/05/30 10:26:59 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


t_token *lst_new(char *input , t_type type)
{
     t_token *node;
      
    node = malloc(sizeof(t_token));
    garbage_collect(node);
    node->value = ft_strdup(input);
    garbage_collect(node->value);
    node->type = type;
    node->next = NULL;
    return (node);
}

void lst_addback(t_token **head, t_token *node)
{
    t_token *tmp;
    
    if(*head == NULL)
        *head = node;
    else
    {
        tmp = *head;
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = node;
    }   
}

t_token *_pipe(int *i)
{
    t_token *tmp;
        
    tmp = lst_new("|" , PIPE);
    *i += 1;
    return(tmp);
}

t_token *_heredoc_in(int *i , char c)
{
    t_token *tmp;
    
    if(c != '<' )
    {
        tmp = lst_new("<" , INPUT);
        *i += 1;
    }
    else
    {
        tmp = lst_new("<<" , HEREDOC);
        *i += 2;
    }
    return (tmp);
}

t_token *_app_out(int *i , char c)
{
    t_token *tmp;
    if(c != '>')
        {
            tmp = lst_new(">" , OUTPUT);
            *i += 1;
        }
        else
        {
            tmp = lst_new(">>" , APPEND);
            *i += 2;
        }
    return (tmp);
}
t_token *_double_quotes(char *input , int *i)
{
    int j;
    int k = 0;
    t_token *tmp;
    
    j = *i + 1;
    while(input[j] && input[j] != '"')
    {
        j++;
        k++;
    }
    if(input[j] == '\0')
        garbage_collect(NULL); //syntax error unclosed double quote" we should write it after this line
    else
    {
        tmp = lst_new(ft_strndup(&input[*i + 1] , k - 1) , WORD);
        *i += j + 1;
    }
    return (tmp);
}

t_token *_single_quotes(char *input , int *i)
{
      int j;
    int k = 0;
    t_token *tmp;
    
    j = *i + 1;
    while(input[j] && input[j] != '\'')
    {
        j++;
        k++;
    }
    if(input[j] == '\0')
        garbage_collect(NULL); //syntax error unclosed double quote" we should write it after this line
    else
    {
        tmp = lst_new(ft_strndup(&input[*i + 1] , k - 1) , WORD);
        *i += j + 1;
    }
    return (tmp);
}

t_token *_word(char *input , int *i)
{
    t_token *tmp;
    int j;
    int k;
    
    j = *i;
    k = 0;
    while(input[j] && is_metachar(input[j]) == 0 && is_whitespace(input[j]) == 0)
    {
        j++;
        k++;
    }
    tmp = lst_new(ft_strndup(&input[*i] , k - 1) , WORD);
    *i = j;
    return (tmp);
}

t_token *check_operator(char *input , int *i)
{
    t_token *tmp = NULL;
    int j;
    int k = 0;
    if(input[*i] == '|')
        tmp = _pipe(i);
    else if(input[*i] == '<')
        tmp = _heredoc_in(i , input[*i + 1]);
    else if(input[*i] == '>')
        tmp = _app_out(i , input[*i + 1]);
    else if(input[*i] == '"')
        tmp = _double_quotes(input , i);
    else if(input[*i] == '\'')
        tmp = _single_quotes(input , i);
    else // word
        tmp = _word(input , i);
    return (tmp);
}


t_token *tokenizer(char *input)
{
    t_token *head = NULL;
    int i = 0;
    while(input[i])
    {
        while(input[i] && is_whitespace(input[i]))
            i++;
        lst_addback(&head , check_operator(input , &i)); 
    }
    return head;
}
 