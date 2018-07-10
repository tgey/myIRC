/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** client chained list
*/

#include "server.h"

cli_t	*empty_client(void)
{
	cli_t	*client = malloc(sizeof(cli_t));

	client->username = NULL;
	client->nickname = NULL;
	client->realname = NULL;
	client->hostname = NULL;
	client->servername = NULL;
	client->last = false;
	client->user = false;
	client->nick = false;
	client->channel = NULL;
	client->channels = init_chained_list(&delete_channel_ptr,
	&destroy_channel_list);
	return (client);
}

cli_t	*get_client_by_nickname(void *list, char *nick)
{
	chained_t	*current = ((chained_list_t *)list)->first;

	while (!current->last) {
		if (((cli_t *)current->data)->nickname &&
		!strcmp(nick, ((cli_t *)current->data)->nickname))
			return (current->data);
		current = current->next;
	}
	return (NULL);
}

cli_t	*get_client_by_fd(void *list, int fd)
{
	chained_t	*current = ((chained_list_t *)list)->first;

	while (!current->last) {
		if (fd == ((cli_t *)current->data)->fd)
			return (current->data);
		current = current->next;
	}
	return (NULL);
}

void	print_list_client(int fd, data_serv_t *serv, void *list, int code)
{
	chained_t	*current = ((chained_list_t *)list)->first;
	int	i = 0;

	while (!current->last) {
		sprintf(serv->to_send, ":localhost %i :%-8s\r\n", code,
		((cli_t *)current->data)->nickname);
		send(fd, serv->to_send, strlen(serv->to_send), 0);
		current = current->next;
		i += 1;
	}
	serv->to_send[0] = 0;
}

void	delete_client_fd(void *list, void *fd)
{
	chained_t	*current = ((chained_list_t *)list)->first;
	int	i = 0;

	while (!current->last) {
		if (((cli_t *)current->data)->fd == *((int *)fd)) {
			delete_chained_list(list, i);
			break;
		}
		current = current->next;
		i += 1;
	}
}
