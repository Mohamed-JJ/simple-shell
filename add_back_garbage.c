#include "main.h"

/**
 * add_back_garbage - adds an item to the bargage list
 *
 * @head: head of the list
 *
 * @data: value of the current item
 */

void    add_back_garbage(t_garbage **head, void *data)
{
	t_garbage *new;
	t_garbage *tmp;

	new = malloc(sizeof(t_garbage));
	if (!new)
		return;
	new->ptr = data;
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		return;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

