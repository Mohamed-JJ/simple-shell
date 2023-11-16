#include "main.h"

/**
 * _builtin - checks if a command is built in
 *
 * @cmd: command
 *
 * Return: true / false
 */

int _builtin(char *cmd)
{
	if (!cmd[0])
		return (0);
	if (!_strcmp(cmd, "cd"))
		return (1);
	if (!_strcmp(cmd, "env"))
		return (1);
	if (!_strcmp(cmd, "exit"))
		return (1);
	return (0);
}
