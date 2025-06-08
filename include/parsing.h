/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:52:07 by yel-alja          #+#    #+#             */
/*   Updated: 2025/06/08 18:38:16 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include "minishell.h"

typedef struct s_token t_token;

/*************token*************/

t_token *tokenizer(char *input);


/*************garbage_collect*************/
void garbage_collect(void *ptr);


/*************syntax*************/
int check_syntax(t_token *token);
int check_quotes(char *input);



/*************utils*************/
char *ft_strndup(char *str , int size);
int is_whitespace(char c);
int is_metachar(char c);
int is_operator(t_token *token);


#endif