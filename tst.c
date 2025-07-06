#include "include/minishell.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/***************** */


int main(int argc, char const *argv[], char *env[])
{
	char *cmd = strdup("pwd");
	int exit_status;

	if (is_path(cmd) == false)
	{
		if (search_in_path(cmd) == false)
		{
			printf("command not found\n");
			exit_status = 127;
		}
	}
	printf("------------\n%s\n", cmd);
	return 0;
}
