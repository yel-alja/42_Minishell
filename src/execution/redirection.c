/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:25:24 by zouazrou          #+#    #+#             */
/*   Updated: 2025/06/29 22:53:46 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	here_doc(char *del, int fd)
{
	char	*line;
	int		fds[2];

	if (!isatty(fd))
		close(fd);
	if (!del)
		return (errmsg(NULL, "here-doc", "Delimiter Not Found"), -1);
	if (pipe(fds) == -1)
		return (errmsg(NULL, "pipe", NULL), -1);
	while (1)
	{
		line = readline(">");
		if (!line)
			return (errmsg("readline", NULL, NULL), close(fds[0]), close(fds[1]), -1);
		if (!ft_strcmp(del, line))
			return (close(fds[1]), free(line), fds[0]);
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
		free(line);
	}
	return (0);
}

int	rd_input(char *file, int fd)
{
	if (!isatty(fd))
		close(fd);
	if (!file)
		return (errmsg(NULL, "<", "Filename Not Found"), -1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		errmsg(NULL, file, NULL);
	return (fd);
}

// If the file does not exist, it shall be created
// otherwise, it shall be truncated to be an empty file after being opened.
int	rd_output(char *file, int fd)
{
	if (!isatty(fd))
		close(fd);
	if (!file)
		return (errmsg(NULL, ">", "Filename Not Found"), -1);
	fd = open(file, O_CREAT | O_TRUNC | O_WRONLY);
	if (fd == -1)
		errmsg(NULL, file, NULL);
	return (fd);
}

int	rd_append(char *file, int fd)
{
	if (!isatty(fd))
		close(fd);
	if (!file)
		return (errmsg(NULL, ">>", "Filename Not Found"), -1);
	fd = open(file, O_CREAT | O_WRONLY | O_APPEND);
	if (fd == -1)
		errmsg(NULL, file, NULL);
	return (fd);
}

char *create_name()
{
    return ("/tmp/herdoc.txt");
}

int heredoc(char *del)
{
	char *file = create_name();
	int fd = open(file , O_RDWR | O_CREAT , 0644);
	char *line = NULL;
	while(1)
	{
		line  = readline(">");
		if(!ft_strcmp(line , del))
			break;
		ft_putstr_fd(line , fd);
		ft_putstr_fd("\n" , fd);
	}
	return fd;
}

// int main(int argc, char *argv[])
// {
// 	int fd = STDIN_FILENO;
// 	(void)argc;
// 	// (void)argv;

// 	fd = re_input(argv[1], fd);
// 	// printf("pathfile:\"%s\" | fd : %d\n", argv[1], fd);
// 	if (fd == -1)
// 		return (1);
// 	int pid = fork();
// 	if (pid == -1)
// 		errmsg(NULL, "fork", NULL);
// 	if (pid == 0)
// 	{
// 		dup2(fd, STDIN_FILENO);
// 		close(fd);
// 		char *args[] = {"cat", NULL};
// 		execve("/bin/cat", args, NULL);
// 		errmsg(NULL, "execve",NULL);
// 		exit(errno);
// 	}
// 	waitpid(pid, NULL, 0);
// 	close(fd);
// 	return 0;
// }

/*
cc redirection.c ../built-in/commands.c ../../libraries/libft/.c -o exe

*/
