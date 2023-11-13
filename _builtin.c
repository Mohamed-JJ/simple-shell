#include "main.h"

/**
 * _builtin - checks if a command is built in
 *
 * @cmd: command
 *
 * Return: true / false
 */

bool _builtin(char *cmd)
{
	if (!cmd[0])
		return (false);
	if (!_strcmp(cmd, "cd"))
		return (true);
	if (!_strcmp(cmd, "env"))
		return (true);
	return (false);
}
