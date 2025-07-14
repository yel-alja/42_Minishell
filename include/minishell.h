/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 23:32:25 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/14 11:13:54 by yel-alja         ###   ########.fr       */
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

#define PROMPT "yzsh> "
#define WHITE_SP " \t\n"

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
	AMBG,
}				t_type;

typedef struct	s_redir
{
    char			*filename;
    t_type			type;
    struct s_redir	*next;
}					t_redir;

typedef struct	s_cmd
{
	char 			*cmd;
	char			**args;
	int				fd_input;
	int				fd_output;
	bool			error;
	t_redir 		*redirects;
	pid_t			pid;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_token
{
	char *value;
	t_type type;
	int amg;
	int flag;
	struct s_token *next;
}	t_token;

typedef struct s_garbage
{
	char *ptr;
	struct s_garbage *next;
}	t_garbage;

/*******signal******/
void	ctrl_c(int sig);
int	exe_cmd_line(t_cmd *cmd, int *exit_status, t_env **env);
int	exe_cmd_line(t_cmd *cmd, int *exit_status, t_env **env);
//?
char *ft_getenv(char *name , t_env *env);
char *expansion(char *token , t_env *env , int flag);
char	*heredoc_file(char *del ,t_env *env , int quoted);

#endif
