/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-alja <yel-alja@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:41:22 by yel-alja          #+#    #+#             */
/*   Updated: 2025/07/28 16:41:23 by yel-alja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// ANSI color codes
#define GREEN "\001\033[1;32m\002"
#define BLUE "\001\033[1;34m\002"
#define YELLOW "\001\033[1;33m\002"
#define RESET "\001\033[0m\002"

char	*get_username(void)
{
	struct passwd	*pw;

	pw = getpwuid(getuid());
	return (pw ? pw->pw_name : "user");
}

char	*get_cwd(void)
{
	static char	cwd[102];

	return (getcwd(cwd, sizeof(cwd)));
}

char	*build_prompt(void)
{
	char *user = get_username();
	char *cwd = get_cwd();

	// Static buffer (enough for typical prompts)
	static char prompt[102 + 100];

	snprintf(prompt, sizeof(prompt),
		GREEN "%s" RESET ":" BLUE "%s" RESET YELLOW " $ " RESET, user, cwd);

	return (prompt);
}