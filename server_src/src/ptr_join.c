/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** join fct ptr
*/

#include "server.h"

bool	error_join(int client_fd, char *cmd, cli_t *client)
{
	char	str[512];
	char	**tab;

	tab = my_str_to_wordtab(cmd, ' ');
	if (tab_len(tab) == 1) {
		sprintf(str, ":localhost 461 %s %s :Not enough parameters\r\n",
		client->nickname, tab[0]);
		send(client_fd, str, strlen(str), 0);
		free_tab(tab);
		return (true);
	}
	free_tab(tab);
	return (false);
}

void	channel_join_names(int client_fd, data_serv_t *serv, char *chan,
cli_t *client)
{
	names_chan(client_fd, serv, chan, client);
	end_of_names(client_fd, serv, chan, client);
}

void	channel_joining(int client_fd, data_serv_t *serv, char *chan,
cli_t *client)
{
	char	str[512];
	chan_t	*channel = get_channel_by_name(serv->channels, chan);
	chan_t	*new_channel;

	if (channel && !get_client_by_fd(channel->clients, client_fd)) {
		insert_chained_list(channel->clients, client);
		insert_chained_list(client->channels, channel);
		sprintf(str, ":%s!%s@%s JOIN :%s", CNI, CUS, CHO, chan);
		tell_channel(client, serv, chan, str);
		channel_join_names(client_fd, serv, chan, client);
	} else if (!channel) {
		new_channel = empty_channel(chan);
		insert_chained_list(new_channel->clients, client);
		insert_chained_list(serv->channels, new_channel);
		insert_chained_list(client->channels,
		get_channel_by_name(serv->channels, chan));
		sprintf(str, ":%s!%s@%s JOIN :%s", CNI, CUS, CHO, chan);
		tell_channel(client, serv, chan, str);
		channel_join_names(client_fd, serv, chan, client);
	}
}

void	ptr_join(int client_fd, data_serv_t *serv, char *cmd,
cli_t *client)
{
	int	i = 4;
	char	**chans;
	char	str[512];

	if (error_join(client_fd, cmd, client))
		return;
	while (cmd[i] == ' ')
		i += 1;
	chans = my_str_to_wordtab(&cmd[i], ',');
	for (int x = 0; chans[x]; x++) {
		if (chans[x][0] != '#') {
			sprintf(str,
			":localhost 403 %s %s :No such channel\r\n",
			client->nickname, chans[x]);
			send(client_fd, str, strlen(str), 0);
		} else
			channel_joining(client_fd, serv, chans[x], client);
	}
	free_tab(chans);
}
