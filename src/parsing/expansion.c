/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 09:06:36 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/04 08:48:19 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int check_dollar(char *str)
{
    int i = 0;
    while(str[i])
    {
        if(str[i] == '$')
            return (1);
        i++;
    }
    return (0);
}

char *remove_name(char *str ,char *str_rm)
{
    int i = 0;
    int j = 0;
    char *res = malloc(ft_strlen(str) - ft_strlen(str_rm) + 1);
    while(str[i])
    {
        if(!ft_strncmp(&str[i] , str_rm , ft_strlen(str_rm)))
        {
            i += ft_strlen(str_rm);
        }
        res[j] = str[i];
        j++;
        i++;
    }
    res[j] = '\0';
    return (res);
}

char *search_and_replace(char **token , char *var_name, char *var_val , int nalen)
{
    int i= 0;
    int j;
    char *tkn = (*token);
    int len = ft_strlen(tkn) + ft_strlen(var_val) - nalen + 1;
    char *res = malloc(len + 1);
    // garbage_collect(res);
    while(i < len)
    {
        if(!ft_strncmp(&tkn[i] , var_name , nalen))
        {
            j = 0;
            while(var_val[j])
            {
                res[i] =  var_val[j];
                i++;
                j++;
            }
        }
        else
        {
            res[i] = tkn[i];
        }
        i++;
    }
    res[i] = '\0';
    *token = remove_name(tkn , var_name);
    return res;
}

char *var(char *token)
{
    int i = 0;
    int start = 0;
    char *var_name= NULL;
    char *var_value = NULL;
    char *p = NULL;

    while(token[i])
    {
        if(token[i] == '$')
        {
            i++;
            start = i;
            while(token[start] && !is_whitespace(token[start]) &&
                        token[start] != '$')
                start++;
            var_name = ft_substr(token , i - 1, start - i + 1); //? garbage collect also for strdup bellow
            // garbage_collect(var_name);
            var_value = getenv(var_name + 1);                        //we should implement our getenv
            if(!var_value)
                continue;
            p = ft_strjoin(p , search_and_replace(&token , var_name , var_value ,ft_strlen(var_name)));
            i = -1;
        }
        i++;
    }
    return (p);
}

char *expansion(char *token)
{
    char *res = NULL;
    if(!check_dollar(token))
        return token;
    res = var(token);
    return res;
}

/*	Notes:
		if value begin by whitespases then split him from prev token
		else join prev token with first word from value
		ex : var=" A B "  ; echo a$var -> "a" "A" "B"
		ex : var="\vA A " ; echo a$var -> "a\vA" "B"
*/

// this fn take value of variable and return lst of token
t_token	*word_splitting(char *value)
{
	t_token	*head;
	char	*word;
	int		i;
	int		len;

	if (!value)
		return (NULL);
	i = 0;
	head = NULL;
	while (value[i])
	{
		while (value[i] && is_whitespace(value[i]))
			i++;
		if (!value[i])
			break;
		len = ft_charlen(value + i, WHITE_SP);
		word = ft_substr(value + i, 0, len);
		// printf("len = %d | word = \"%s\"\n", len, word);
		token_add_back(&head, new_token(word, WORD));
		free(word);
		word = NULL;
		i += len;
	}
	return (head);
}
