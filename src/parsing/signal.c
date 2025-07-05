/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:02:31 by zouazrou          #+#    #+#             */
/*   Updated: 2025/07/04 17:40:18 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// extern int	signal_code;

void	ctrl_c(int sig)
{
	(void )sig;
	write(2, "\n", 1);
	rl_replace_line("", 0); // clear buffer : second param like ctrl z in 'vs'
	rl_on_new_line(); // move to new line
	rl_redisplay(); // reprint promt
	// signal_code = sig;
}
