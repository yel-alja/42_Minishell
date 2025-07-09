/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:02:31 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/09 10:05:53 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// extern int	signal_code;

void	ctrl_c(int sig)
{
	int	*code;

	(void )sig;
	code = get_addr_exit_status(NULL);
	*code = sig + 128;
	write(2, "\n", 1);
	rl_replace_line("", 0); // clear buffer : second param like ctrl z in 'vs'
	rl_on_new_line(); // move to new line
	rl_redisplay(); // reprint promt
	// signal_code = sig;
}
