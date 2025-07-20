/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:27:14 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/20 17:54:01 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	execution(t_cmd *cmd)
{
	if (cmd && ((is_built_in(cmd) || !cmd->cmd) && !cmd->next))
		exe_single_built_in(cmd);
	else
		exe_pipeline_cmd(cmd);
}

void	init_our_shell(int *status, t_env **envp, char **env_parent)
{
	*status = 0;
	*envp = NULL;
	get_addr_env(envp);
	get_addr_exit_status(status);
	rl_outstream = stderr;
	*envp = get_envp(env_parent);
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **env_parent)
{
	int		status;
	char	*input;
	t_cmd	*cmd;
	t_env	*envp;
	t_token	*token;

	(void)av;
	(void)ac;
	init_our_shell(&status, &envp, env_parent);
	while (1)
	{
		cmd = NULL;
		input = readline(PROMPT);
		if (!input)
			ft_clean(true, true, *get_addr_exit_status(NULL));
		garbage_collect(input, false);
		add_history(input);
		token = tokenizer(input);
		cmd = parser(token);
		execution(cmd);
		ft_clean(false, true, -1);
	}
	return (EXIT_SUCCESS);
}
