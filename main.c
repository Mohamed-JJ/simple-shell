#include "main.h"

t_garbage *collector;

void	print_error(char *cmd, char *message)
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
 *
 * Return: /path/cmd
 */

char *_return_join_path(char *cmd, char **env, t_garbage *collector)
{
	char **paths;
	int i;

	if (!cmd)
		return (NULL);
	if (cmd[0] == '/')
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
		print_error(cmd, ": command not found\n");
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
	print_error(cmd, ": command not found\n");
	return (NULL);
}

/**
 * _get_args - get new arguments array
 *
 * @arr: array
 *
 * @collector: garbage collector
 *
 * Return: array of arguments
 */

char **_get_args(char **arr, t_garbage *collector)
{
	char **args;

	args = NULL;
	if (!arr[1])
	{
		args = malloc(sizeof(char *) * 2);
		if (!args)
			return (NULL);
		args[0] = _strdup("");
		args[1] = NULL;
		add_back_garbage(&collector, args[0]);
		add_back_garbage(&collector, args);
	}
	else
	{
		int i;
		int j;

		i = 0;
		while (arr[i])
			i++;
		args = malloc(sizeof(char *) * (i));
		if (!args)
			return (NULL);
		for (j = 0; j < i; j++)
		{
			args[j] = _strdup(arr[j]);
			add_back_garbage(&collector, args[j]);
		}
		add_back_garbage(&collector, args);
		args[i] = NULL;
	}
	return (args);
}

/**
 * _execute - execute command
 *
 * @cmd: command name
 * @env: environment variables
 * @collector: garbage collector
 *
 */

void _execute(char **cmd, char **env, t_garbage *collector)
{
	pid_t pid;
	int status;
	char *joined_path;

	joined_path = _return_join_path(cmd[0], env, collector);
	if (!joined_path)
		return;
	pid = fork();
	if (pid == -1)
	{
		print_error(cmd[0], ": Error: fork failed\n");
		return;
	}
	if (pid == 0)
	{
		if (joined_path)
		{
			char **args = _get_args(cmd, collector);

			if (execve(joined_path, args, env) == -1)
				print_error(cmd[0], ": Error: execve failed\n");
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

/**
 * _check_input - check input and execute it if it exists
 *
 * @input: user input
 * @env: environment variables
 * @collector: garbage collector
 *
 */

void _check_input(char *input, char **env, t_garbage *collector)
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
			exit(0);
		}
	}
	else
		_execute(tab, env, collector);
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
	(void)ac;
	while (1)
	{
		char *input;
		char *inputdup = NULL;
		size_t inputSize = 0;
		collector = NULL;

		printf("%s: ", av[0]);
		if (!getline(&input, &inputSize, stdin))
			return (1);
		inputdup = _strdup(input);
		add_back_garbage(&collector, inputdup);
		if (inputdup == NULL)
			return (1);
		inputdup[_strcspn(inputdup, "\n")] = '\0';
		_check_input(inputdup, env, collector);
		clear_garbage(&collector);
	}
	return (0);
}
