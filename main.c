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

int main(int c, char **v, char **env)
{
    while (1)
	{
        char input[100];
		char *inputdup = NULL;
        printf("%s: ", v[0]);
        inputdup = fgets(input, sizeof(input), stdin);
		addBackGarbage(&collector, inputdup);
		if (inputdup == NULL)
			return 0;
        inputdup[strcspn(inputdup, "\n")] = '\0';
        
        printf("%s\n", inputdup);
		clear_garbage(&collector);
    }

    return 0;
}