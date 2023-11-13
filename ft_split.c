#include "main.h"

/**
 * ft_split - splits a string into tokens
 *
 * @s: given string
 * @c: delimiter
 *
 * Return: an array of tokens extracted from the string
 */

char    **ft_split(char const *s, char c)
{
	char	**tab;
	int	i;
	int	j;
	int	k;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (_strlen(s) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		k = i;
		while (s[i] && s[i] != c)
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


