/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:27:14 by yel-alja          #+#    #+#             */
/*   Updated: 2025/06/08 08:48:24 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char *type_to_str(t_type type)
{
    if (type == PIPE) return "PIPE";
    if (type == APPEND) return "APPEND";
    if (type == OUTPUT) return "REDIR_OUT";
    if (type == INPUT) return "REDIR_IN";
    if (type == HEREDOC) return "HEREDOC";
    return "WORD";
}

void print_tokens(t_token *token)
{
    while(token)
    {
         printf("\033[36m[value : \033[0m\033[33m%s\033[0m\033[36m]    [type : \033[0m\033[32m%s\033[0m\033[36m]\033[0m\n",token->value, type_to_str(token->type));
        token = token->next;
    }
}
void env(t_env *our_env)
{
	while (our_env)
	{
		printf("%s", our_env->name);
		if (our_env->value)
		{
			printf("=");
			printf("%s", our_env->value);
		}
		printf("\n");
		our_env = our_env->next;
	}

}

int main(int ac, char **av, char **env)
{
	t_env	*envp;

	//envp = get_envp(env);
    while(1)
    {
        t_token *token ;
        char *input;
        input = readline("minishell> ");
        if(input)
            add_history(input);
        token = tokenizer(input);
        if(token == NULL)
        {
            garbage_collect(NULL);
            continue;
        }
        print_tokens(token);
    }
}
