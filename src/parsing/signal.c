/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:02:31 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/19 22:24:22 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ctrl_c(int sig)
{
	int	*code;

	code = get_addr_exit_status(NULL);
	*code = sig + 128;
	write(2, "\n", 1);
	rl_replace_line("", 0); // clear buffer : second param like ctrl z in 'vs'
	rl_on_new_line();       // move to new line
	rl_redisplay();         // reprint promt
}

void	here_doc_hanl(int sig)
{
	close(save_fd_here_doc(0));
	ft_putchar_fd('\n', STDOUT_FILENO);
	ft_clean(true, true, sig + 128);
}
