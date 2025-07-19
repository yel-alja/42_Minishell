/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:27:14 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/20 00:19:21 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char *type_to_str(t_type type)
{
    if (type == PIPE) return "PIPE";
    if (type == APPEND) return "APPEND";
    if (type == OUTPUT) return "OUTPUT";
    if (type == INPUT) return "INPUT";
    if (type == AMBG) return "AMBG";
    if (type == HEREDOC) return "HEREDOC";
    return "WORD";
}

void print_tokens(t_token *token)
{
    while(token)
    {
		// if (token->type == WORD)
		// {
		// 	char *ptr = token->value;
		// 	token->value = quote_removal(ptr);
		// 	free(ptr);
		// }
        printf("\033[36m[value : \033[0m\033[33m%s\033[0m\033[36m]    [type : \033[0m\033[32m%s\033[0m\033[36m]\033[0m====%d\n",token->value, type_to_str(token->type) , token->quoted);
        token = token->next;
    }
}


void print_cmd_list(t_cmd *cmd) {
    int index = 0;
    while (cmd) {
        printf("=== Command %d ===\n", index++);
        printf("Command: %s\n", cmd->cmd);

        printf("Args:\n");
        if (cmd->args) {
            for (int i = 0; cmd->args[i]; i++)
                printf("[%s] ", cmd->args[i]);
        }
        printf("\nRedirections:\n");
        if (cmd->redirects) {
            t_redir *red = cmd->redirects;
            while (red) {
                printf("file %s type %s===%d\n", red->filename, type_to_str(red->type) , red->quoted);
                red = red->next;
            }
        }
        printf("\n");
        cmd = cmd->next;
    }
}

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

int main(int ac, char **av, char **env_parent)
{
	int		status;
	char	*input;
	t_cmd	*cmd;
	t_env	*envp;
	t_token	*token;

	(void)av;
	(void)ac;
	init_our_shell(&status, &envp, env_parent);
    while(1)
    {
		cmd = NULL;
        input = readline(PROMPT);
        if(!input)
			ft_clean(true, true, *get_addr_exit_status(NULL));
        garbage_collect(input , false);
		add_history(input);
        token = tokenizer(input);
		cmd = parser(token);
        // print_tokens(token);
        // print_cmd_list(cmd);
		execution(cmd);
		ft_clean(false, true, -1);
    }
	return (EXIT_SUCCESS);
}

/*
cat << eof : ctrl c + sigquit
mini inside mini : retrun sighanl to default when exe cmd until finish waiting command (also in single_built_in)
*/
