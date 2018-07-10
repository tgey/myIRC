/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** list part splitted part
*/

#include "server.h"

void	print_list_elem(int client_fd, data_serv_t *serv, char **args,
chained_t *current)
{
	if (is_in(((chan_t *)current->data)->name, args[1])) {
		sprintf(serv->to_send, "322 %s\r\n",
		((chan_t *)current->data)->name);
		send(client_fd, serv->to_send,
		strlen(serv->to_send), 0);
	}
}

void	clear_client_part(cli_t *client)
{
	if (client->channel)
		free(client->channel);
	client->channel = NULL;
}

bool	join_checker(data_serv_t *serv, char **args, cli_t *client)
{
	if (tab_len(args) < 2) {
		sprintf(serv->to_send, "461 \"%s\":Not enough parameters\r\n",
		args[0]);
		return (false);
	}
	if (client->channel) {
		sprintf(serv->to_send,
		"405 %s :You have joined too many channels\r\n", args[1]);
		return (false);
	}
	return (true);
}