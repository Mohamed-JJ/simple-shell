# include <libc.h>


typedef	struct s_cmd
{
	char	*cmd;
	char	**args;
	char	**env;
	char	**out_files;
}				t_cmd;


typedef struct s_garbage
{
	void	*ptr;
	struct s_garbage	*next;
}				t_garbage;
// first we have ti o split the input and organize the data, once we've done that we can  start to work on the execution of the command

t_garbage *collector = NULL;

void	addBackGarbage(t_garbage **head, void *data)
{
	t_garbage *new;
	t_garbage *tmp;

	new = malloc(sizeof(t_garbage));
	if (!new)
		return ;
	new->ptr = data;
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	clear_garbage(t_garbage **head)
{
	t_garbage *tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->ptr);
		if (tmp)
			free(tmp);
	}
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (strlen(s) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c))
			i++;
		k = i;
		while (s[i] && (s[i] != c))
			i++;
		if (i > k)
		{
			tab[j] = malloc(sizeof(char) * (i - k + 1));
			if (!tab[j])
				return (NULL);
			strlcpy(tab[j], s + k, i - k + 1);
			j++;
		}
	}
	tab[j] = NULL;
	return (tab);
}

int main(int c, char **v, char **env)
{
	(void)c;
	(void)env;
    while (1)
	{
        char input[100];
		char *inputdup = NULL;
        printf("%s: ", v[0]);
        fgets(input, sizeof(input), stdin);
		inputdup = strdup(input);
		addBackGarbage(&collector, inputdup);
		if (inputdup == NULL)
			return (1);
        inputdup[strcspn(inputdup, "\n")] = '\0';        
		clear_garbage(&collector);
    }

    return 0;
}