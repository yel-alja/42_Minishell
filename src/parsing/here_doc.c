/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:55:28 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/20 00:19:07 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*create_name(void)
{
	int		i;
	int		fd;
	char	c;
	char	*file;

	file = malloc(SIZE_FILE_NAME);
	garbage_collect(file, true);
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (NULL);
	i = 0;
	while (i < SIZE_FILE_NAME)
	{
		if (read(fd, &c, 1) == -1)
			return (close(fd), NULL);
		if (ft_isalnum(c))
			file[i++] = c;
	}
	file[SIZE_FILE_NAME - 1] = '\0';
	close(fd);
	file = ft_strjoin("/tmp/", file);
	return (file);
}

int	save_fd_here_doc(int fd)
{
	static int	stock = -1;

	if (stock == -1)
		stock = fd;
	return (stock);
}

void	read_here_doc(char *del, int quoted, int fd)
{
	char	*line;
	int		*status;

	status = get_addr_exit_status(NULL);
	*status = EXIT_SUCCESS;
	while (1)
	{
		line = readline(">");
		if (!line)
		{
			close(fd);
			errmsg("warning", "here-document delimited by end-of-file wanted",
					del);
			ft_clean(true, true, EXIT_SUCCESS);
		}
		garbage_collect(line, false);
		if (!ft_strcmp(line, del))
		{
			close(fd);
			ft_clean(true, true, EXIT_SUCCESS);
		}
		if (!quoted)
			line = expansion(line, 0);
		ft_putendl_fd(line, fd);
	}
}

char	*heredoc_file(char *del, int quoted)
{
	char	*file;
	int		fd;
	int		pid;

	file = create_name();
	fd = open(file, O_RDWR | O_CREAT, 0644);
	if (!file || fd == -1)
		return (errmsg("here-doc", "I/O syscalls", NULL), NULL);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (errmsg("here-doc", "fork", NULL), NULL);
	if (pid == 0)
	{
		save_fd_here_doc(fd);
		signal(SIGINT, here_doc_hanl);
		read_here_doc(del, quoted, fd);
	}
	close(fd);
	waitpid(pid, get_addr_exit_status(NULL), 0);
	signal(SIGINT, ctrl_c);
	decode_exit_status();
	if (*get_addr_exit_status(NULL) == SIGINT + 128)
		return (NULL);
	return (file);
}
