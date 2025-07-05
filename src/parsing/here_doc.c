/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:55:28 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/04 22:09:53 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	has_quote(char *del)
{
	int	i;

	i = -1;
	while (del[++i])
	{
		if (del[i] == '"' || del[i] == '\'')
			return (true);
	}
	return (false);
}
char *create_name()
{
	// we should 
    return ("/tmp/herdoc.txt");
}
/*
	-> why fork ?
*/
char	*here_doc_file(char *del)
{
	char	*file;
	char	*line;
	bool	expansion;
	int		fd;

	file = create_name();
	fd = open(file, O_RDWR | O_CREAT | O_APPEND);
	expansion = has_quote(del);
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
		if (expansion == true)
			/***expension***/;
		ft_putstr_fd(line , fd);
		ft_putstr_fd("\n" , fd);
	}
	return (file);
}
