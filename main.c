# include "main.h"

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

char	**ft_split_spaces(char const *s)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

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

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

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

char	*_getenv(char **env)
{
	int	i;

	i = 0;
	if (env == NULL)
		return (NULL);
	while (env[i])
	{
		if (env[i])
		{
			if (!strncmp(env[i], "PATH=", 5))
				return (env[i] + 5);
		}
		i++;
	}
	return (NULL);
}


char	*_return_join_path(char *cmd, char **env)
{
	char	**paths;

	paths = ft_split(_getenv(env), ':');
	addBackGarbage(&collector, paths);
	for (int i = 0; paths[i]; i++)
		addBackGarbage(&collector, paths[i]);
	if (paths)
	{
		for (int i = 0; paths[i]; i++)
		{
			char *joined_path = NULL;
			joined_path = malloc(sizeof(char) * (_strlen(paths[i]) + _strlen(cmd) + 2));
			if (!joined_path)
				return (NULL);
			strcpy(joined_path, paths[i]);
			strcat(joined_path, "/");
			strcat(joined_path, cmd);
			addBackGarbage(&collector, joined_path);
			if (access(joined_path, F_OK) == 0)
				return (joined_path);
		}
	}
	// on here sould be the program name, i just hard coded it here
	printf("a.out: command not found: %s\n", cmd);
	return (NULL);
}

bool	_builtin(char *cmd)
{
	if (!!cmd[0])
		return (false);
	if (!_strcmp(cmd, "cd"))
		return (true);
	if (!_strcmp(cmd, "env"))
		return (true);
	return (false);
}

void	_execute_builtin(char **cmd, char **env)
{
	int	i;

	i = 0;
	if (!_strcmp(cmd[0], "cd"))
	{
		if (!cmd[1])
			return ;
		if (chdir(cmd[1]) == -1)
			printf("cd: %s: No such file or directory\n", cmd[1]);
	}
	if (!_strcmp(cmd[0], "env"))
	{
		while (env[i])
		{
			printf("%s\n", env[i]);
			i++;
		}
	}
}

char	**_get_args(char **arr)
{
	char	**args;

	args = NULL;
	if (!arr[1])
	{
		args = malloc(sizeof(char *) * 2);
		if (!args)
			return (NULL);
		args[0] = strdup("");
		args[1] = NULL;
		addBackGarbage(&collector, args[0]);
		addBackGarbage(&collector, args);
	}
	else {
		int i = 0;
		while (arr[i])
			i++;
		args = malloc(sizeof(char *) * (i));
		if (!args)
			return (NULL);
		for (int j = 0; j < i; j++)
		{
			args[j] = strdup(arr[j]);
			addBackGarbage(&collector, args[j]);
		}
		addBackGarbage(&collector, args);
		args[i] = NULL;
	}
	return (args);
}

void	_execute(char **cmd, char **env)
{
	pid_t	pid;
	int		status;
	char	*joined_path;

	joined_path = _return_join_path(cmd[0], env);
	pid = fork();
	if (pid == -1)
	{
		// here should be program name
		printf("Error: fork failed\n");
		return ;
	}
	if (pid == 0)
	{
		if (joined_path)
		{
			char **args = _get_args(cmd);
			if (execve(joined_path, args, env) == -1)
			// here should be program name
				printf("Error: execve failed\n");
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

void	_check_input(char *input, char **env)
{
	char	**tab;

	if (input[0] == '\0' || !input)
		return ;
	tab = ft_split_spaces(input);
	if (!tab)
		return ;
	addBackGarbage(&collector, tab);
	for (int i = 0; tab[i]; i++)
		addBackGarbage(&collector, tab[i]);
	if (_builtin(tab[0]))
		_execute_builtin(tab, env);
	else
	{
	 	_execute(tab, env);
	}
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
		if (!fgets(input, sizeof(input), stdin))
			return (1);
		inputdup = strdup(input);
		addBackGarbage(&collector, inputdup);
		if (inputdup == NULL)
			return (1);
		inputdup[_strcspn(inputdup, "\n")] = '\0';  
		_check_input(inputdup, env);
		clear_garbage(&collector);
	}
	return 0;
}
