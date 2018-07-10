/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** tell channel the update
*/

#include "server.h"

void	tell_client(chained_list_t *clients, UNUSED data_serv_t *serv,
char *msg, chan_t *channel)
{
	chained_t	*current = channel->clients->first;
	cli_t	*client;

	while (!current->last) {
		client = (cli_t *)current->data;
		if (!get_client_by_fd(clients, client->fd)) {
			send(client->fd, msg, le(msg), 0);
			insert_chained_list(clients, client);
		}
		current = current->next;
	}
}

void	tell_once_all_channel(cli_t *client, data_serv_t *serv, char *msg)
{
	chained_list_t	*clients = init_chained_list(&delete_client_fd,
	&destroy_client_list);
	chained_t	*current = client->channels->first;
	chan_t	*channel;

	while (!current->last) {
		channel = (chan_t *)current->data;
		tell_client(clients, serv, msg, channel);
		current = current->next;
	}
	clients->destroy(clients);
}

void	tell_channel(UNUSED cli_t *client, data_serv_t *serv, char *name,
char *msg)
{
	char	str[512];
	chan_t	*channel = get_channel_by_name(serv->channels, name);
	chained_t	*current;
	int	cfd;

	if (channel) {
		sprintf(str, "%s\r\n", msg);
		current = channel->clients->first;
		while (!current->last) {
			cfd = ((cli_t *)current->data)->fd;
			send(cfd, str, le(str), 0);
			current = current->next;
		}
	}
}

void	tell_channel_others(cli_t *client, chan_t *channel, char *msg)
{
	chained_t	*current = channel->clients->first;
	int	cfd;

	while (!current->last) {
		cfd = ((cli_t *)current->data)->fd;
		if (cfd != client->fd)
			send(cfd, msg, le(msg), 0);
		current = current->next;
	}
}