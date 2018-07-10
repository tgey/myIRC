/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** privmsg fct ptr
*/

#include "server.h"

bool	error_privmsg(int client_fd, char *cmd, cli_t *client)
{
	char	**tab = my_str_to_wordtab(cmd, ' ');
	char	str[512];
	int	len = tab_len(tab);

	if (len == 1 || (len >= 2 && tab[1][0] == ':')) {
		sprintf(str,
		":localhost 411 %s :No recipient given (PRIVMSG)",
		client->nickname);
		send(client_fd, str, le(str), 0);
		free_tab(tab);
		return (true);
	} else if (len == 2) {
		sprintf(str,
		":localhost 412 %s :No text to send",
		client->nickname);
		send(client_fd, str, le(str), 0);
		free_tab(tab);
		return (true);
	}
	return (false);
}

void	privmsg_channel(cli_t *client, data_serv_t *serv, char *msg,
char *target)
{
	char	str[512];
	chan_t	*channel = get_channel_by_name(serv->channels, target);

	if (channel) {
		channel = get_channel_by_name(client->channels, target);
		if (channel) {
			sprintf(str, ":%s!%s@%s PRIVMSG %s :%s\r\n",
			CNI, CUS, CHO, target, msg);
			tell_channel_others(client, channel, str);
		} else {
			sprintf(str,
			":localhost 404 %s %s :Cannot send to channel\r\n",
			client->nickname, target);
			send(client->fd, str, le(str), 0);
		}
	} else {
		sprintf(str,
		":localhost 401 %s %s :No such nick/channel\r\n",
		client->nickname, target);
		send(client->fd, str, le(str), 0);
	}
}

void	privmsg_client(cli_t *client, data_serv_t *serv, char *msg,
char *target)
{
	cli_t	*cli = get_client_by_nickname(serv->list, target);
	char	str[512];

	if (cli) {
		sprintf(str, ":%s!%s@%s PRIVMSG %s :%s\r\n",
		CNI, CUS, CHO, target, msg);
		send(cli->fd, str, le(str), 0);
	} else {
		sprintf(str,
		":localhost 401 %s %s :No such nick/channel\r\n",
		client->nickname, target);
		send(client->fd, str, le(str), 0);
	}
}

void	send_msg(cli_t *client, data_serv_t *serv, char *msg, char *cmd)
{
	char	**tab = my_str_to_wordtab(cmd, ' ');
	char	**targets = my_str_to_wordtab(tab[1], ',');

	for (int i = 0; targets[i]; i++) {
		if (targets[i][0] == '#')
			privmsg_channel(client, serv, msg, targets[i]);
		else
			privmsg_client(client, serv, msg, targets[i]);
	}
	free_tab(targets);
	free_tab(tab);
}

void	ptr_privmsg(int client_fd, data_serv_t *serv, char *cmd,
cli_t *client)
{
	int	i = 7;

	if (error_privmsg(client_fd, cmd, client))
		return;
	while (cmd[i] == ' ')
		i += 1;
	while (cmd[i] && cmd[i] != ' ')
		i += 1;
	while (cmd[i] == ' ')
		i += 1;
	if (cmd[i] == ':')
		i += 1;
	send_msg(client, serv, &cmd[i], cmd);
}