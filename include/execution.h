/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 09:03:24 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/30 10:04:28 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "minishell.h"

typedef struct s_env t_env;

bool	is_path(char *file);
bool	is_built_in(char *cmd);

// Redirections
// int		here_doc(char *del, int fd);
char     *heredoc(char *del);
int		rd_input(char *file, int fd);
int		rd_output(char *file, int fd);
int		rd_append(char *file, int fd);

// Built-in commands
int		echo(char **args);
int		pwd(char **args);
int		cd(char **args);
// int		env(char **args, t_env **env);
// int		export(char **args, t_env **env);
// int		unset(char **args, t_env **env);
// int		exit(char **args);

// Error o dakchi
void	errmsg(char *cmd, char *arg, char *msg);


/******** envp *********/
t_env	*get_envp(char **env);
//utils
int	ft_charlen(char *str, char c);


#endif
