/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** msg handling
*/

#include "server.h"

void	send_to_user(UNUSED int client_fd, data_serv_t *serv, char *msg,
char *nick)
{
	cli_t	*client = get_client_by_nickname(serv->list, nick);
	char	*message = malloc(sizeof(char) * (strlen(msg) + 3));

	message[0] = 0;
	message = strcat(message, msg);
	message = strcat(message, "\r\n");
	if (client && client->fd != client_fd) {
		send(client->fd, message, le(message), 0);
		sprintf(serv->to_send, "SENDED\n");
	}
	else
		sprintf(serv->to_send, "401 \"%s\":No such nick/channel\r\n",
		nick);
	free(message);
}

char	*init_message(char *msg, cli_t *client)
{
	char	*str = my_strcat("", "PRIVMSG ");

	if (client)
		str = my_ccat(str, client->nickname);
	else
		str = my_ccat(str, "unknown");
	str = my_ccat(str, " :");
	str = my_ccat(str, msg);
	str = my_ccat(str, "\r\n");
	return (str);
}

void	send_in_channel(int client_fd, data_serv_t *serv, char *msg)
{
	cli_t	*client = get_client_by_fd(serv->list, client_fd);
	chan_t	*chan;
	chained_t	*current = NULL;
	char	*mesg = init_message(msg, client);

	if (!client)
		return;
	if (client->channel) {
		chan = get_channel_by_name(serv->channels, client->channel);
		if (chan)
			current = chan->clients->first;
	}
	if (!current)
		return;
	while (!current->last) {
		if (((cli_t *)current->data)->fd != client_fd)
			send(((cli_t *)current->data)->fd, mesg, le(mesg), 0);
		current = current->next;
	}
	free(mesg);
}
