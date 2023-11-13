#include "main.h"

/**
 * _strncmp - compares two strings and returns an int
 *
 * @s1: first string
 *
 * @s2: second string
 *
 * @n: number of characters to compare
 *
 * Return: the difference of first different char
 */

int _strncmp(char *s1, char *s2, unsigned int n)
{
	while (*s1 != '\0' && n > 0)
	{
		if (*s1 < *s2 || *s1 > *s2)
		{
			return ((int)(*s1 - *s2));
		}
		if (*s1 != '\0')
			s1++;
		if (*s2 != '\0')
			s2++;
		n--;
	}
	return (0);
}
