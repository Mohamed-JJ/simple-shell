#include "../main.h"

/**
 * _strlen - returns the lenght of a string
 *
 * @s: given string
 *
 * Return: length of string @s
 */

int _strlen(char const *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
