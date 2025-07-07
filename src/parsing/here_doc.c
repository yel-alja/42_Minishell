/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:55:28 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/07 10:33:49 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	has_quote(char *del)
{
	int	i;

	i = -1;
	while (del[++i])
	{
		if (del[i] == '"' || del[i] == '\'')
			return (1);
	}
	return (0);
}
char *create_name()
{
	// we should 
    return ("/tmp/herdoc.txt");
}

char	*here_doc_file(char *del ,t_env *env)
{
	char	*file;
	char	*line;
	int		exp;
	int		fd;

	file = create_name();
	fd = open(file, O_RDWR | O_CREAT , 0644);
	exp = has_quote(del);
	while (1)
	{
		line = readline(">");
		if (!line)
		{
			printf("warning: here-document delimited by end-of-file (wanted `a')\n"); //should we write error in 2
			break;
		}
		if (!ft_strcmp(line, del))
			break;
		// if (!exp)
			// line = expansion(line ,env);
		ft_putstr_fd(line , fd);
		ft_putstr_fd("\n" , fd);
	}
	return (file);
}
