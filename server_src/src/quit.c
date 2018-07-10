/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** client quit
*/

#include "server.h"

bool	removing_client(data_serv_t *serv, int client_fd, int i)
{
	char	str[512];
	cli_t	*client;

	if (serv->events[i].data.fd == client_fd) {
		client = get_client_by_fd(serv->list, client_fd);
		sprintf(str,
		":localhost ERROR %s :Closing Link: %s (Client Quit)\r\n",
		client->nickname, client->hostname);
		send(client_fd, str, le(str), 0);
		delete_client_all(serv, client_fd);
		close(serv->events[i].data.fd);
		serv->events[i].events = 0;
		printf("Removing client fd %d\n", serv->events[i].data.fd);
		serv->events[i].data.fd = -1;
		return (true);
	}
	return (false);
}

void	check_if_last(chained_list_t *users, chained_list_t *chans,
char *name)
{
	if (chained_list_len(users) == 0) {
		chans->del(chans, name);
	}
}

void	delete_client_all(data_serv_t *serv, int fd)
{
	chained_t	*current = ((chained_list_t *)serv->channels)->first;
	chained_t	*tmp;
	int	i = 0;

	while (!current->last) {
		tmp = current;
		((chan_t *)tmp->data)->
		clients->del(((chan_t *)tmp->data)->clients, &fd);
		current = current->next;
		check_if_last(((chan_t *)tmp->data)->clients,
		serv->channels, ((chan_t *)tmp->data)->name);
		i += 1;
	}
	serv->list->del(serv->list, &fd);
}

void	send_cmd_quit(int client_fd, data_serv_t *serv, char **tab)
{
	if (strcmp(tab[0], "QUIT") != 0)
		send(client_fd, serv->to_send,
		strlen(serv->to_send), 0);
}
