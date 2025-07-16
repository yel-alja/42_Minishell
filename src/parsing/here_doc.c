/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:55:28 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/15 16:11:27 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *create_name()
{
	char rd;
	int fd;
	int i  = 0;
	int bytes;
	char *file = malloc(20);
	garbage_collect(file , 0);
	fd = open("/dev/random" , O_RDONLY);
	if(fd == -1)
	{
		garbage_collect(NULL,  1); //?
	}
	while(i < 20)
	{
		bytes  = read(fd , &rd , 1);
		if(ft_isalpha(rd))
		{
			file[i] = rd;
			i++;
		}
	}
	file[20] = '\0';
	close(fd);
	file = ft_strjoin("/tmp/" , file);
    return (file);
}

char	*heredoc_file(char *del ,t_env *env , int quoted)
{
	char	*file;
	char	*line;
	int		fd;
	int pid;
	int status;
	file = create_name();
	fd = open(file, O_RDWR | O_CREAT , 0644);
	pid = fork();
	if(pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			line = readline(">");
			garbage_collect(line, 1);
			if (!line)
			{
				write(2 , "warning: here-document delimited by end-of-file (wanted `a')\n" , 61); //should we write error in 2
				close(fd);
				garbage_collect(NULL, 1);
				exit(0);
			}
			if (!ft_strcmp(line, del))
			{
				close(fd);
				exit(0);
			}
			if(!quoted)
			{
				line = expansion(line ,env , 0);
			}
			ft_putstr_fd(line , fd);
			ft_putstr_fd("\n" , fd);
		}
	}
	close(fd);
	waitpid(pid ,&status ,0);
	return (file);
}
