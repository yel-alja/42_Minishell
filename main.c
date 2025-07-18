/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:27:14 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/18 08:55:05 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	signal_code;

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

void printenv(t_env *e, bool d_x)
{
    while(e)
    {
		if (d_x == true)
			printf("declare -x %s=\"%s\"\n" , e->name , e->value);
		else
			printf("%s=%s\n" , e->name , e->value);
        e = e->next;
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

int main(int ac, char **av, char **env)
{
	t_env	*envp;
	t_token *token;
    // printenv(envp);
	t_cmd	*cmd;
	int		exit_status;
	char *input;

	(void)av;
	(void)ac;
	exit_status = 0;
	envp = NULL;
	get_addr_env(&envp);
	get_addr_cmd(&cmd);
	get_addr_exit_status(&exit_status);
	envp = get_envp(env); 
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
    while(1)
    {
		cmd = NULL;
        input = readline(PROMPT);
        if(!input)
		{
            garbage_collect(input , false);
            free_env();
			exit(*get_addr_exit_status(NULL));
		}
        garbage_collect(input , true);
		add_history(input);
        token = tokenizer(input);

        if(token == NULL)
        {
            garbage_collect(NULL , false);
            continue;
        }
		cmd = parser(token);
        // print_tokens(token);
        print_cmd_list(cmd);    
		// if (is_built_in(cmd) && !cmd->next) // "> dsg" SEGV // also $SADGG SEGV
		// 	exe_single_built_in(cmd);
		// else
		// 	exe_pipeline_cmd(cmd);
		printf("[%d]\n", *get_addr_exit_status(NULL));
        garbage_collect(NULL , false);
    }
}
