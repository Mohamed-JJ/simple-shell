#include "main.h"

/**
 * _strdup - duplicates a string and returns the new copy
 *
 * @str: string to copy
 *
 * Return: the new string
 */

char *_strdup(char *str)
{
	char *copy = malloc(sizeof(char) * _strlen(str));
	int i;

	i = 0;
	while (str[i])
	{
		copy[i] = str[i];
		i++;
	}

	return (copy);
}
