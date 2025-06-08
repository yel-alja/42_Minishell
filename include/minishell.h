/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 23:32:25 by yel-alja          #+#    #+#             */
/*   Updated: 2025/06/08 11:41:47 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include "../libft/libft.h"
#include "parsing.h"
#include "execution.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef enum	e_type
{
    PIPE,        // |
    WORD,        // "hello"
    INPUT,       // <
    OUTPUT,      // >
    APPEND,      // >>
    HEREDOC,     // <<
    HEREDOC_Q,	 // << '\"
}				t_type;

typedef struct	s_redir
{
    char			*file_del;
    t_type	type;
    struct s_redir	*next;
}					t_redir;

typedef struct	s_cmd
{
	char			**args;
	int				fd_input;
	int				fd_output;
	bool			error;
	t_redir 		*redirects;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_token
{
	char *value;
	t_type type;
	int quote; //if 0 the value it was not quoted else it was quoted
	struct s_token *next;
}	t_token;

typedef struct s_garbage
{
	char *ptr;
	struct s_garbage *next;
}	t_garbage;


#endif
