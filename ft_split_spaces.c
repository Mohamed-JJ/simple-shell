#include "main.h"

/**
 * ft_split_spaces - splits a string to tokens
 *
 * @s: string
 *
 * Return: table of tokens extracted from @s
 */

char    **ft_split_spaces(char const *s)
{
	char    **tab;
	int             i;
	int             j;
	int             k;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (_strlen(s) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		k = i;
		while (s[i] && (s[i] != ' ' && s[i] != '\t'))
			i++;
		if (i > k)
		{
			tab[j] = malloc(sizeof(char) * (i - k + 1));
			if (!tab[j])
				return (NULL);
			_strncpy(tab[j], s + k, i - k + 1);
			tab[j][i - k] = '\0';
			j++;
		}
	}
	tab[j] = NULL;
	return (tab);
}

