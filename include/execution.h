/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 09:03:24 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/20 00:19:45 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "minishell.h"

typedef struct s_env t_env;


// Redirections
int		rd_input(char *file, int fd);
int		rd_output(char *file, int fd, t_type flag);
int		open_redirects(t_cmd *cmd);

// execution
void	exe_single_built_in(t_cmd *cmd);
bool	is_path(char *file);
int		exec_built_in(t_cmd *cmd);
bool	is_built_in(t_cmd *cmd);

/*******Built-in commands*******/
int		ft_echo(char **args);
int		ft_pwd(char **args);
int		ft_cd(char **args);
int		ft_env(char **args);
int		ft_export(char **args);
int		ft_unset(char **args);
int		ft_exit(char **args);

// Error o dakchi
void	errmsg(char *cmd, char *arg, char *msg);

/******** add *********/
t_env	**get_addr_env(t_env **ptr);
int		*get_addr_exit_status(int *ptr);

/******** envp *********/
t_env	*get_envp(char **env);
void	printenv(t_env *e, bool d_x);

char	**env_to_arr(t_env *env);

void	search_in_path(t_cmd *cmd);
t_env	*new_var(char *var);
void	add_var(t_env *var);
void		sep_name_value(char *var, char **name, char **value);
void		decode_exit_status(void);
bool	is_directory(char *path);

void	ft_clean(bool own_env, bool garbage, int status);
void	here_doc_hanl(int sig);
int	save_fd_here_doc(int fd);

int		ft_charlen(char *str, char *del);
int		ft_close(int *fd);
char	*strdup_org(const char *s);
void	free_env(void);
void	valid_path_executable(t_cmd *cmd);

#endif
