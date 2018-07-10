/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** nick fct ptr
*/

#include "server.h"

bool	validate_nickname(char *nick)
{
	int	i = 0;

	while (nick[i]) {
		if (!is_number(nick[i]) && !is_letter(nick[i]) &&
		!is_special(nick[i]))
			return (false);
		i += 1;
	}
	return (true);
}

bool	already_nick(int client_fd, data_serv_t *serv, char *nick,
cli_t *client)
{
	char	str[512];

	if (get_client_by_nickname(serv->list, nick)) {
		sprintf(str,
		":localhost 433 %s %s :Nickname is already in use\r\n",
		CNI, nick);
		send(client_fd, str, strlen(str), 0);
		free(nick);
		return (true);
	}
	return (false);
}

bool	error_nick(int client_fd, data_serv_t *serv, char *nick,
cli_t *client)
{
	char	str[512];

	if (!nick) {
		sprintf(str, ":localhost 431 %s :No nickname given\r\n",
		CNI);
		send(client_fd, str, strlen(str), 0);
		return (true);
	} else if (!validate_nickname(nick)) {
		sprintf(str, ":localhost 432 %s %s :Erroneus nickname\r\n",
		CNI, nick);
		send(client_fd, str, strlen(str), 0);
		free(nick);
		return (true);
	}
	return (already_nick(client_fd, serv, nick, client));
}

void	nick_send_channel(cli_t *client, data_serv_t *serv, char *nick)
{
	char	str[512];

	sprintf(str, ":%s!%s@%s NICK %s\r\n", CNI, CUS, CHO, nick);
	tell_once_all_channel(client, serv, str);
}

void	ptr_nick(int client_fd, data_serv_t *serv, char *cmd,
cli_t *client)
{
	char	*nick = NULL;
	int	i = 4;

	serv->to_send[0] = 0;
	while (cmd[i] == ' ')
		i += 1;
	if (cmd[i] == ':')
		i += 1;
	if (le(&cmd[i]) > 0)
		nick = strdup(&cmd[i]);
	if (error_nick(client_fd, serv, nick, client))
		return;
	if (client->nick && client->user)
		nick_send_channel(client, serv, nick);
	if (get_client_by_fd(serv->list, client_fd)->nickname)
		free(get_client_by_fd(serv->list, client_fd)->nickname);
	get_client_by_fd(serv->list, client_fd)->nickname = nick;
	if (!client->nick && client->user)
		registration_ending(client_fd, serv, client);
	client->nick = true;
}