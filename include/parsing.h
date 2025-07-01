/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:52:07 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/01 19:00:35 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include "minishell.h"

typedef struct s_token t_token;
typedef struct s_cmd t_cmd;
typedef struct s_redir t_redir;
typedef enum	e_type t_type;

/*************token*************/

t_token *tokenizer(char *input);


/*************garbage_collect*************/
void garbage_collect(void *ptr);


/*************syntax*************/
int check_syntax(t_token *token);
int check_quotes(char *input);

/*************expantion*************/
char *expansion(char *token);
int check_dollar(char *str);

/*************utils*************/
char *ft_strndup(char *str , int size);
int is_whitespace(char c);
int is_metachar(char c);
int is_operator(t_token *token);

/*************parser*************/
void lst_addbackc(t_cmd **head, t_cmd *node);
t_cmd *lst_new_cmd(char *cmd ,char **args , t_redir *red);
void lst_add_back(t_redir **head, t_redir *node);
t_cmd *parser(t_token *token);
t_redir *lst_new_red(char *file , t_type type);
/******quote removal******/
char *quote_removal(char *str);

#endif
