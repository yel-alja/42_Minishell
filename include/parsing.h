/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:52:07 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/20 10:54:25 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include"minishell.h"

typedef struct s_token	t_token;
typedef struct s_cmd	t_cmd;
typedef struct s_redir	t_redir;
typedef struct s_env	t_env;
typedef enum e_type		t_type;

/*************token*************/
t_token		*tokenizer(char *input );
t_token		*new_token(char *input, t_type type, int amg);
void		token_add_back(t_token **head, t_token *node);
int			contains_char(char c, char *str);
t_token		*new_token(char *input, t_type type, int amg);
void		token_add_back(t_token **head, t_token *node);
void		update_amg(t_token *token);
t_token		*build_list(char **res);
t_token		*her_del(char *input, int *i);
t_token		*token_re_input(int *i, char *c);
t_token		*token_re_output(int *i, char c);
char		*quoted_word(char *input, int *i, char *quote);
char		*unquoted_word(char *input, int *i);

/*************garbage_collect*************/
void		garbage_collect(void *ptr, bool terminate);

/*************syntax*************/
int			check_syntax(t_token *token);
int			check_quotes(char *input);

/*************expantion*************/
// char *expansion(char *token , t_env *env);
int			check_dollar(char *str);

/*************utils*************/
int			is_whitespace(char c);
int			is_metachar(char c);
int			is_operator(t_token *token);

/*************parser*************/
void		cmd_add_back(t_cmd **head, t_cmd *node);
t_cmd		*new_cmd(char *cmd, char **args, t_redir *red);
void		red_add_back(t_redir **head, t_redir *node);
t_cmd		*parser(t_token *token );
t_redir		*new_red(char *file, t_type type);

/******quote removal******/
char		*quote_removal(char *str);

#endif
