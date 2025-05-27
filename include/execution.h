/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 09:03:24 by zouazrou          #+#    #+#             */
/*   Updated: 2025/05/27 11:24:12 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

t_bool	is_path(char *file);
t_bool	is_built_in(char *cmd);

// Redirections
int		here_doc(char *del, int fd);
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

#endif
