# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

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

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->env = NULL;
	cmd->out_files = NULL;
	return (cmd);
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

char	**ft_split(char const *s)
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
			strlcpy(tab[j], s + k, i - k + 1);
			j++;
		}
	}
	tab[j] = NULL;
	return (tab);
}

bool	_operator(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (strcmp(tab[i], ">") == 0 || strcmp(tab[i], ">>") == 0)
			return (true);
		i++;
	}
	return (false);
}

void	execute_cmd_redirections(char **tab)
{
	int	i;
	int	fd;
	int	fd2;

	i = 0;
	while (tab[i])
	{
		if (strcmp(tab[i], ">") == 0)
		{
			fd = open(tab[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			fd2 = dup(1);
			dup2(fd, 1);
			close(fd);
			tab[i] = NULL;
			tab[i + 1] = NULL;
			execvp(tab[0], tab);
			dup2(fd2, 1);
			close(fd2);
			return ;
		}
		i++;
	}
	execvp(tab[0], tab);

}

void	_check_input(char *input)
{
	t_cmd	*cmd;
	int		file = 1;
	char	**tab;

	tab = ft_split(input);
	addBackGarbage(&collector, tab);
	for (int i = 0; tab[i]; i++)
	{
		printf("tab[%d] = %s\n", i, tab[i]);
		addBackGarbage(&collector, tab[i]);
	}
	if (!tab)
		return ;
	if (_operator(tab) == true)
		return (execute_cmd_redirections(tab));
	cmd = init_cmd();
	if (!cmd)
		return ;
	cmd->cmd = strdup(tab[0]);
	cmd->args = tab + 1;
	addBackGarbage(&collector, cmd->cmd);
	addBackGarbage(&collector, cmd);
	// in here we are going to execute the command, by getting the path from the env and checking all the paths and seeing if that file exists or not
	
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
		_check_input(inputdup);
		clear_garbage(&collector);
    }
    return 0;
}