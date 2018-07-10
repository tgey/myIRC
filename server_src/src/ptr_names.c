/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** names fct ptr
*/

#include "server.h"

void	names_chan(int client_fd, data_serv_t *serv, char *chan,
cli_t *client)
{
	char	str[512];
	chan_t	*channel = get_channel_by_name(serv->channels, chan);
	chained_t	*current = channel ? channel->clients->first : NULL;
	int	i = 0;

	if (channel) {
		sprintf(str, ":localhost 353 %s = %s :", client->nickname,
		chan);
		send(client_fd, str, le(str), 0);
		while (!current->last) {
			sprintf(str, i == 0 ? "%s" : " %s",
			((cli_t *)current->data)->nickname);
			send(client_fd, str, le(str), 0);
			current = current->next;
			i += 1;
		}
		sprintf(str, "\r\n");
		send(client_fd, str, le(str), 0);
	}
}

void	end_of_names(int client_fd, data_serv_t *serv, char *chan,
cli_t *client)
{
	char	str[512];

	if (get_channel_by_name(serv->channels, chan)) {
		sprintf(str, ":localhost 366 %s %s :End of /NAMES list\r\n",
		client->nickname, chan);
		send(client_fd, str, le(str), 0);
	}
}

int	names_without_channel(int client_fd, data_serv_t *serv,
cli_t *client)
{
	chained_t	*current = serv->list->first;
	cli_t	*cli;
	int	i = 0;
	char	str[512];

	while (!current->last) {
		cli = (cli_t *)current->data;
		if (i == 0 && chained_list_len(cli->channels) == 0) {
			sprintf(str, ":localhost 353 %s = %s :",
			client->nickname, "*");
			send(client_fd, str, le(str), 0);
		}
		if (chained_list_len(cli->channels) == 0) {
			sprintf(str, i == 0 ? "%s" : " %s", cli->nickname);
			send(client_fd, str, le(str), 0);
			i += 1;
		}
		current = current->next;
	}
	return (i);
}

void	names_global(int client_fd, data_serv_t *serv, cli_t *client)
{
	chained_t	*current = serv->channels->first;
	char	str[512];

	while (!current->last) {
		names_chan(client_fd, serv, ((chan_t *)current->data)->name,
		client);
		end_of_names(client_fd, serv, ((chan_t *)current->data)->name,
		client);
		current = current->next;
	}
	if (names_without_channel(client_fd, serv, client) != 0) {
		sprintf(str, "\r\n");
		send(client_fd, str, le(str), 0);
		sprintf(str, ":localhost 366 %s %s :End of /NAMES list\r\n",
		client->nickname, "*");
		send(client_fd, str, le(str), 0);
	}
}

void	ptr_names(int client_fd, data_serv_t *serv, char *cmd,
cli_t *client)
{
	int	i = 5;
	char	**tab;

	while (cmd[i] == ' ')
		i += 1;
	if (cmd[i]) {
		tab = my_str_to_wordtab(&cmd[i], ',');
		for (int x = 0; tab[x]; x++) {
			names_chan(client_fd, serv, tab[x], client);
			end_of_names(client_fd, serv, tab[x], client);
		}
		free_tab(tab);
	} else
		names_global(client_fd, serv, client);
}