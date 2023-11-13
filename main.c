#include "main.h"

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
	printf("%s: command not found\n", cmd);
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
	pid = fork();
	if (pid == -1)
	{
		printf("%s: Error: fork failed\n", cmd[0]);
		return;
	}
	if (pid == 0)
	{
		if (joined_path)
		{
			char **args = _get_args(cmd, collector);

			if (execve(joined_path, args, env) == -1)
				printf("%s: Error: execve failed\n", cmd[0]);
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
		_execute_builtin(tab, env);
	else
	{
		_execute(tab, env, collector);
	}
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
	(void)env;
	while (1)
	{
		char *input;
		char *inputdup = NULL;
		size_t inputSize = 0;
		t_garbage *collector = NULL;

		printf("%s: ", av[0]);
		if (!getline(&input, &inputSize, stdin))
			return (1);
		inputdup = _strdup(input);
		add_back_garbage(&collector, input);
		add_back_garbage(&collector, inputdup);
		if (inputdup == NULL)
			return (1);
		inputdup[_strcspn(inputdup, "\n")] = '\0';
		_check_input(inputdup, env, collector);
		clear_garbage(&collector);
	}
	return (0);
}
