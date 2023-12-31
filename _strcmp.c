#include "main.h"

/**
 * _strcmp - compares two strings and returns an int
 *
 * @s1: first string
 *
 * @s2: second string
 *
 * Return: the difference of first different char
 */

int _strcmp(char *s1, char *s2)
{
	if (_strlen(s1) > _strlen(s2))
	{
		while (*s1 != '\0')
		{
			if (*s1 < *s2 || *s1 > *s2)
			{
				return ((int)(*s1 - *s2));
			}
			if (*s1 != '\0')
				s1++;
			if (*s2 != '\0')
				s2++;
		}
	}
	else
	{
		while (*s2 != '\0')
		{
			if (*s1 < *s2 || *s1 > *s2)
			{
				return ((int)(*s1 - *s2));
			}
			if (*s1 != '\0')
				s1++;
			if (*s2 != '\0')
				s2++;
		}
	}
	return (0);
}
