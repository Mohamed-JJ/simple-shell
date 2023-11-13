#include "main.h"

/**
 * _execute_builtin - execute builtin command
 *
 * @cmd: command
 *
 * @env: environment variables
 *
 */

void _execute_builtin(char **cmd, char **env)
{
	int i;

	i = 0;
	if (!_strcmp(cmd[0], "cd"))
	{
		if (!cmd[1])
			return;
		if (chdir(cmd[1]) == -1)
			printf("cd: %s: No such file or directory\n", cmd[1]);
	}
	if (!_strcmp(cmd[0], "env"))
	{
		while (env[i])
		{
			printf("%s\n", env[i]);
			i++;
		}
	}
}
