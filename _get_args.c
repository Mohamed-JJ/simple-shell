#include "main.h"

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
