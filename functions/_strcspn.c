#include "../main.h"

/**
 * _strcspn - get span until character in string
 * @str: string
 *
 * @str2: characters to look for
 *
 * Return: size of the new string
 */

size_t _strcspn(char *str, char *str2)
{
	size_t i, x;

	i = 0;
	while (str[i])
	{
		for (x = 0; str2[x] && (str2[x] != str[i]); x++)
		{}

		if (str2[x] == str[i])
			break;
		i++;
	}

	return (i);
}
