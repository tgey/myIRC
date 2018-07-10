/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** chained list handling
*/

#include "server.h"

int	chained_list_len(chained_list_t *list)
{
	chained_t	*current = list->first;
	int	i = 0;

	while (!current->last) {
		current = current->next;
		i += 1;
	}
	return (i);
}

chained_list_t	*init_chained_list(void (*del)(void *, void *),
	void (*destroy)(void *))
{
	chained_list_t	*list = malloc(sizeof(*list));
	chained_t	*first = malloc(sizeof(*first));

	first->data = NULL;
	first->next = NULL;
	first->last = true;
	list->first = first;
	list->del = del;
	list->destroy = destroy;
	return (list);
}

void	insert_chained_list(chained_list_t *list, void *data)
{
	chained_t	*new = malloc(sizeof(*new));

	new->next = list->first;
	new->data = data;
	new->last = false;
	list->first = new;
}

void	delete_chained_list(chained_list_t *list, int index)
{
	int	i = 1;
	chained_t	*current = list->first;
	chained_t	*tmp = NULL;

	if (index == 0 && list->first != NULL) {
		tmp = list->first;
		list->first = list->first->next;
	}
	while (!current->last) {
		if (i == index && current != NULL && current->next != NULL) {
			tmp = current->next;
			current->next = current->next->next;
			break;
		}
		current = current->next;
		i += 1;
	}
	if (tmp)
		free(tmp);
}
