/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** channel chained list
*/

#include "server.h"

chan_t	*empty_channel(char *name)
{
	chan_t	*channel = malloc(sizeof(chan_t));

	channel->name = strdup(name);
	channel->clients = init_chained_list(&delete_client_fd,
	&destroy_client_list);
	return (channel);
}

chan_t	*get_channel_by_name(void *list, char *name)
{
	chained_t	*current = ((chained_list_t *)list)->first;

	while (!current->last) {
		if (!strcmp(name, ((chan_t *)current->data)->name))
			return (current->data);
		current = current->next;
	}
	return (NULL);
}

void	print_list_channel(int client_fd, data_serv_t *serv, void *list)
{
	chained_t	*current = ((chained_list_t *)list)->first;
	char	str[512];

	while (!current->last) {
		sprintf(str, ":localhost 322 %s %d :[+nt]\r\n",
		((chan_t *)current->data)->name,
		chained_list_len(((chan_t *)current->data)->clients));
		send(client_fd, str, le(str), 0);
		current = current->next;
	}
	serv->to_send[0] = 0;
}

void	delete_channel_ptr(void *list, void *ptr)
{
	chained_t	*current = ((chained_list_t *)list)->first;
	int	i = 0;

	while (!current->last) {
		if (!strcmp(((chan_t *)current->data)->name, (char *)ptr)) {
			delete_chained_list(list, i);
			break;
		}
		current = current->next;
		i += 1;
	}
}
