/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:07:38 by moirhira          #+#    #+#             */
/*   Updated: 2025/05/27 11:37:24 by zouazrou         ###   ########.fr       */
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
#include "../libft/libft.h"


typedef enum	e_bool
{
	FALSE,
	TRUE,
}				t_bool;

#include "execution.h"
#include "parsing.h"


typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef enum	e_redir_type
{
    PIPE,        // |
    INPUT,       // <
    OUTPUT,      // >
    APPEND,      // >>
    HEREDOC,     // <<
    HEREDOC_Q,
}				t_redir_type;

typedef struct	s_redir
{
    char			*file_del;
    t_redir_type	type;
    struct s_redir	*next;
}					t_redir;

/*

ex: cmd arg1 arg2 < infile << EOF > outfile1 >> outfile2
struct
{
	char **args = {"cmd", "arg1", "arg2", NULL}
	t_redir : {linked list}
	("infile", INPUT) -> ("EOF", HEREDOC) -> ("outfile1", INPUT) -> ("outfile2", APPEND) -> NULL
	next = NULL
}
*/

typedef struct	s_cmd
{
	char			**args;
	int				fd_input;
	int				fd_output;
	t_bool			error;
	t_redir 		*redirects;
	struct s_cmd	*next;
}					t_cmd;

#endif
