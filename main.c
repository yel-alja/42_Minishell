/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:27:14 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/13 11:23:07 by zouazrou         ###   ########.fr       */
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
        printf("\033[36m[value : \033[0m\033[33m%s\033[0m\033[36m]    [type : \033[0m\033[32m%s\033[0m\033[36m]\033[0m\n",token->value, type_to_str(token->type));
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
                printf("%s ", cmd->args[i]);
        }
        printf("\nRedirections:\n");
        if (cmd->redirects) {
            t_redir *red = cmd->redirects;
            while (red) {
                printf("file %s type %s\n", red->filename, type_to_str(red->type));
                red = red->next;
            }
        }
        printf("\n");
        cmd = cmd->next;
    }
}

void here_doc(t_cmd *cmd ,t_env *env) // just for testing
{

    while(cmd)
    {
     t_redir *red = cmd->redirects;
     while(red)
     {
        if(red->type == HEREDOC)
            red->filename = here_doc_file(red->filename , env);
        red = red->next;
     }
     cmd = cmd->next;
    }
}

//'dsfjl"f'''das"'
int main(int ac, char **av, char **env)
{
	t_env	*envp;
	t_token *token;
	t_cmd	*cmd;
	int		exit_stat;
	char *input;

	(void)av;
	(void)ac;
	exit_stat = 0;
	get_addr_env(&envp);
	get_addr_cmd(&cmd);
	get_addr_exit_status(&exit_stat);
	envp = get_envp(env);
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
    while(1)
    {
		cmd = NULL;
        input = readline(PROMPT);
        garbage_collect(input , 0);
        if(!input)
		{
			// clean up
			exit(EXIT_SUCCESS);
		}
		add_history(input);
		token = tokenizer(input);
        if(token == NULL)
        {
            garbage_collect(NULL , 1);
            continue;
        }
		cmd = parser(token);
		here_doc(cmd , envp);
        // print_tokens(token);
		if (is_built_in(cmd) && !cmd->next)
			exe_single_built_in(cmd);
		else
			exe_pipeline_cmd(cmd);
		// printf("[%d]\n", *get_addr_exit_status(NULL));
        garbage_collect(NULL , 1);
    }
}
