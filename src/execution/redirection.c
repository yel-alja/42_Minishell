/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 09:25:24 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/05 11:11:13 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	rd_input(char *file, int fd)
{
	ft_close(&fd);
	if (!file)
		return (errmsg(NULL, "red", "Filename Not Found"), -1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		errmsg(NULL, file, NULL);
	return (fd);
}

// If the file does not exist, it shall be created
// otherwise, it shall be truncated to be an empty file after being opened.
int	rd_output(char *file, int fd, t_type flag)
{
	ft_close(&fd);
	if (!file)
		return (errmsg(NULL, "red", "Filename Not Found"), -1);
	if (flag == APPEND)
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0664);
	if (flag == OUTPUT)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd == -1)
		errmsg(NULL, file, NULL);
	return (fd);
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
