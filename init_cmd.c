# include "main.h"

/**
 * init_cmd - initalizes a cmd structure
 *
 * Return: pointer to new cmd
 */


t_cmd   *init_cmd(void)
{
	t_cmd   *cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->env = NULL;
	cmd->out_files = NULL;
	return (cmd);
}

