#include "main.h"

/**
 * _getenv - get environment variables
 *
 * @env: array of environment variables
 *
 * Return: all paths
 */

char    *_getenv(char **env)
{
	int     i;

	i = 0;
	if (env == NULL)
		return (NULL);
	while (env[i])
	{
		if (env[i])
		{
			if (!_strncmp(env[i], "PATH=", 5))
				return (env[i] + 5);
		}
		i++;
	}
	return (NULL);
}

