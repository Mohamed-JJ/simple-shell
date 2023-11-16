#include "main.h"

/**
 * clear_garbage - frees memory by clearing garbage list
 *
 * @head: head of the list
 */

void    clear_garbage(t_garbage **head)
{
	t_garbage *tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		if (tmp)
		{
			if (tmp->ptr)
			{
				free(tmp->ptr);
				tmp->ptr = NULL;
			}
			free(tmp);
		}
	}
	(*head) = NULL;
}
