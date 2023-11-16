#include "main.h"

/**
 * _print_error - print error message in the STDERR_FILENO
 *
 * @cmd: command
 * @message: error message
 *
 */

void _print_error(char *cmd, char *message)
{
	write(STDERR_FILENO, cmd, _strlen(cmd));
	write(STDERR_FILENO, message, _strlen(message));
}

/**
 * _return_join_path - joins a path with cmd name
 *
 * @cmd: command
 * @env: environment variables
 * @collector: garbage collector
 * @status: status
 * Return: /path/cmd
 */

char *_return_join_path(char *cmd,
						char **env,
						t_garbage *collector,
						int *status)
{
	char **paths;
	int i;

	if (!cmd)
		return (NULL);
	if (cmd[0] == '/')
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
		_print_error(cmd, ": command not found\n");
		*status = 127;
		return (NULL);
	}
	paths = ft_split(_getenv(env), ':');
	add_back_garbage(&collector, paths);
	for (i = 0; paths[i]; i++)
		add_back_garbage(&collector, paths[i]);
	if (paths)
	{
		for (i = 0; paths[i]; i++)
		{
			char *joined_path = NULL;

			joined_path = malloc(sizeof(char) * (_strlen(paths[i]) + _strlen(cmd) + 2));
			if (!joined_path)
				return (NULL);
			_strcpy(joined_path, paths[i]);
			_strcat(joined_path, "/");
			_strcat(joined_path, cmd);
			add_back_garbage(&collector, joined_path);
			if (access(joined_path, F_OK) == 0)
				return (joined_path);
		}
	}
	_print_error(cmd, ": command not found\n");
	*status = 127;
	return (NULL);
}

/**
 * _execute - execute command
 *
 * @cmd: command name
 * @env: environment variables
 * @collector: garbage collector
 * @status: status
 */

void _execute(char **cmd, char **env, t_garbage *collector, int *status)
{
	pid_t pid;
	char *joined_path;

	joined_path = _return_join_path(cmd[0], env, collector, status);
	if (!joined_path)
		return;
	pid = fork();
	if (pid == -1)
	{
		_print_error(cmd[0], ": Error: fork failed\n");
		return;
	}
	if (pid == 0)
	{
		if (joined_path)
		{
			char **args = _get_args(cmd, collector);

			if (execve(joined_path, args, env) == -1)
				_print_error(cmd[0], ": Error: execve failed\n");
		}
	}
	else
	{
		waitpid(pid, status, 0);

		if (WIFEXITED(*status))
			*status = WEXITSTATUS(*status);
	}
}

/**
 * _check_input - check input and execute it if it exists
 *
 * @input: user input
 * @env: environment variables
 * @collector: garbage collector
 * @status: status
 */

void _check_input(char *input, char **env, t_garbage *collector, int *status)
{
	char **tab;
	int i;

	if (input[0] == '\0' || !input)
		return;
	tab = ft_split_spaces(input);
	if (!tab)
		return;
	add_back_garbage(&collector, tab);
	for (i = 0; tab[i]; i++)
		add_back_garbage(&collector, tab[i]);
	if (_strcmp(tab[0], "exit") == 0)
		exit(0);
	if (_builtin(tab[0]))
	{
		if (_execute_builtin(tab, env) == 1)
		{
			clear_garbage(&collector);
			exit(*status);
		}
	}
	else
		_execute(tab, env, collector, status);
}

/**
 * main - simple shell
 *
 * @ac: argument count
 * @av: argument vector
 * @env: environment variables
 *
 * Return: 0 on success, 1 on error
 */

int main(int ac, char **av, char **env)
{
	int status = 0;
	(void)ac;

	while (1)
	{
		t_garbage *collector;
		char *input;
		int code;
		char *inputdup = NULL;
		size_t inputSize = 0;

		collector = NULL;

		if (isatty(STDIN_FILENO))
			printf("%s: ", av[0]);
		code = getline(&input, &inputSize, stdin);
		if (code == -1)
			exit(status);

		inputdup = _strdup(input);
		add_back_garbage(&collector, inputdup);
		if (inputdup == NULL)
			return (1);
		inputdup[_strcspn(inputdup, "\n")] = '\0';
		_check_input(inputdup, env, collector, &status);
		clear_garbage(&collector);
	}
	return (0);
}
