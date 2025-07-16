/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:55:28 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/16 13:43:30 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *create_name()
{
	char rd;
	int fd;
	int i;
	char *file;

	file = malloc(20);
	garbage_collect(file , true);
	fd = open("/dev/random" , O_RDONLY);
	i = 0;
	while(i < 20)
	{
		if (read(fd , &rd , 1) == -1)
			garbage_collect(NULL,  true);
		if(ft_isalpha(rd))
			file[i++] = rd;
	}
	file[20] = '\0';
	close(fd);
	file = ft_strjoin("/tmp/" , file);
    return (file);
}

char	*heredoc_file(char *del , int quoted)
{
	char	*file;
	char	*line;
	int		fd;
	int pid;

	file = create_name();
	fd = open(file, O_RDWR | O_CREAT , 0644);
	pid = fork();
	if(pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			line = readline(">");
			if (!line)
			{
				errmsg("warning", NULL, "here-document delimited by end-of-file (wanted `a')"); //should we write error in 2
				close(fd);
				garbage_collect(line, true);
				exit(0);
			}
			garbage_collect(line, true);
			if (!ft_strcmp(line, del))
			{
				close(fd);
				garbage_collect(NULL, true);
				exit(0);
			}
			if(!quoted)
				line = expansion(line , 0);
			ft_putendl_fd(line , fd);
		}
	}
	close(fd);
	waitpid(pid , get_addr_exit_status(NULL),0);
	process_exit_status();
	return (file);
}
