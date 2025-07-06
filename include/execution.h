/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 09:03:24 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/05 17:57:34 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "minishell.h"

typedef struct s_env t_env;

bool	is_path(char *file);
bool	is_built_in(char *cmd);

// Redirections
// int		open_here_doc(char *del, int fd);
int		rd_input(char *file, int fd);
int		rd_output(char *file, int fd, t_type flag);

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
int	ft_charlen(char *str, char *del);
int ft_close(int *fd);
bool	search_in_path(t_cmd *cmd);


#endif
