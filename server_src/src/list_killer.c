/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** list killing
*/

#include "server.h"

void	free_client(cli_t *client)
{
	if (client->username)
		free(client->username);
	if (client->nickname)
		free(client->nickname);
	if (client->realname)
		free(client->realname);
	if (client->hostname)
		free(client->hostname);
	if (client->servername)
		free(client->servername);
}

void	kill_client_list(chained_list_t *list)
{
	chained_list_t	*ptr = ((chained_list_t *)list);
	chained_t	*current = ptr->first;

	while (!current->last) {
		free_client((cli_t *)current->data);
		free(current->data);
		delete_chained_list(list, 0);
		current = ptr->first;
	}
	free(ptr->first);
	free(ptr);
}

void	destroy_client_list(void *list)
{
	chained_list_t	*ptr = ((chained_list_t *)list);
	chained_t	*current = ptr->first;

	while (!current->last) {
		delete_chained_list(list, 0);
		current = ptr->first;
	}
	free(ptr->first);
	free(ptr);
}

void	destroy_channel_list(void *list)
{
	chained_list_t	*ptr = ((chained_list_t *)list);
	chained_t	*current = ptr->first;
	chan_t	*channel;

	while (!current->last) {
		((chained_list_t *)((chan_t *)current->data)->clients)
		->destroy(((chained_list_t *)((chan_t *)current
		->data)->clients));
		channel = ((chan_t *)current->data);
		if (channel->name)
			free(channel->name);
		free(channel);
		delete_chained_list(list, 0);
		current = ptr->first;
	}
	free(ptr->first);
	free(ptr);
}
