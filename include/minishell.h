/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 23:32:25 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/20 17:55:42 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "parsing.h"
# include "execution.h"

# define PROMPT "\033[0;35myzsh> \033[0m"
# define SH_NAME "yzsh"
# define SIZE_FILE_NAME 20
# define WHITE_SP " \t\n"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef enum e_type
{
	PIPE,
	WORD,
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC,
	AMBG,
}				t_type;

typedef struct s_redir
{
	char			*filename;
	int				quoted;
	t_type			type;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				fd_input;
	int				fd_output;
	bool			error;
	t_redir			*redirects;
	pid_t			pid;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_token
{
	char			*value;
	t_type			type;
	int				amg;
	int				quoted;
	struct s_token	*next;
}	t_token;

typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;
}	t_garbage;

/*******signal******/
void	ctrl_c(int sig);
void	exe_pipeline_cmd(t_cmd *cmd);

char	*ft_getenv(char *name);
char	*expansion(char *token, int flag);
char	*heredoc_file(char *del, int quoted);
t_env	*ft_getvarenv(char *name);

#endif
