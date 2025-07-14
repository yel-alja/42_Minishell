/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:27:14 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/14 11:59:58 by yel-alja         ###   ########.fr       */
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
        printf("\033[36m[value : \033[0m\033[33m%s\033[0m\033[36m]    [type : \033[0m\033[32m%s\033[0m\033[36m]\033[0m\n",token->value, type_to_str(token->type));
        token = token->next;
    }
}

void printenv(t_env *e)
{
    while(e)
    {
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
                printf("file %s type %s\n", red->filename, type_to_str(red->type));
                red = red->next;
            }
        }
        printf("\n");
        cmd = cmd->next;
    }
}


void check_red(t_cmd *cmd , t_env  *env , int flag) // just for testing
{

    while(cmd)
    {
     t_redir *red = cmd->redirects;
     while(red)
     {
        if(red->type == HEREDOC)
        {
            heredoc_file(red->filename, env , flag);
        }
        red = red->next;
     }
     cmd = cmd->next;
    }
}

//'dsfjl"f'''das"'
// void free_env(t_env *env)
// {
//     t_env *tmp;
//     while(env)
//     {
//         tmp = env;
//         env = env->next;
//         free(tmp->name);
//         free(tmp->value);
//         free(tmp);
        
//     }
// }
int main(int ac, char **av, char **env)
{
	t_env	*envp;
	t_token *token;
    t_cmd *cmd;
	char *input;
    (void )av;
    (void )ac;
	envp = get_envp(env);
    // printenv(envp);
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
    while(1)
    {
        input = readline(PROMPT);
        garbage_collect(input , 0);
        if(!input)
		{
			// clean up
            garbage_collect(NULL , 1);
            // free_env(envp);            
			exit(EXIT_SUCCESS);
		}
		add_history(input);
        token = tokenizer(input , envp);
        if(token == NULL)
        {
            garbage_collect(NULL , 1);
            continue;
        }
        cmd = parser(token);
        // check_red(cmd , envp , 1);
		// exe_cmd_line(parser(token), &ac, &envp);
        
        print_cmd_list(cmd);
        garbage_collect(NULL , 1);
    }
}
