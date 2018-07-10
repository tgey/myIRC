/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** part fct ptr
*/

#include "server.h"

bool	error_part(int client_fd, UNUSED data_serv_t *serv, char *cmd,
cli_t *client)
{
	char	**tab = my_str_to_wordtab(cmd, ' ');
	char	str[512];

	if (tab_len(tab) <= 1) {
		sprintf(str, ":localhost 461 %s %s :Not enough parameters\r\n",
		client->nickname, tab[0]);
		send(client_fd, str, strlen(str), 0);
		free_tab(tab);
		return (true);
	}
	free_tab(tab);
	return (false);
}

void	leave_channel(int client_fd, data_serv_t *serv, chan_t *channel,
cli_t *client)
{
	channel->clients->del(channel->clients, &client_fd);
	client->channels->del(client->channels, channel->name);
	if (chained_list_len(channel->clients) < 1)
		serv->channels->del(serv->channels, channel->name);
}

void	part_channel(int client_fd, data_serv_t *serv, char *chan,
cli_t *client)
{
	char	str[512];
	chan_t	*channel = get_channel_by_name(serv->channels, chan);
	chan_t	*cli_chan = get_channel_by_name(client->channels, chan);

	if (!channel) {
		sprintf(str, ":localhost 403 %s %s :No such channel\r\n",
		client->nickname, chan);
		send(client_fd, str, strlen(str), 0);
		return;
	}
	if (!cli_chan) {
		sprintf(str,
		":localhost 442 %s %s :You're not on that channel\r\n",
		client->nickname, chan);
		send(client_fd, str, strlen(str), 0);
		return;
	}
	sprintf(str, ":%s!%s@%s PART %s", CNI, CUS, CHO, chan);
	tell_channel(client, serv, chan, str);
	leave_channel(client_fd, serv, channel, client);
}

void	ptr_part(int client_fd, data_serv_t *serv, char *cmd,
cli_t *client)
{
	int	i = 4;
	char	**tab;

	if (error_part(client_fd, serv, cmd, client))
		return;
	while (cmd[i] == ' ')
		i += 1;
	tab = my_str_to_wordtab(&cmd[i], ',');
	for (int x = 0; tab[x]; x++) {
		part_channel(client_fd, serv, tab[x], client);
	}
}