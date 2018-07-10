/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** quit fct ptr
*/

#include "server.h"

void	ptr_quit(int client_fd, data_serv_t *serv, char *cmd,
cli_t *client)
{
	int	i = 4;
	char	str[512];

	while (cmd[i] == ' ')
		i += 1;
	if (cmd[i] == ':')
		i += 1;
	if (!cmd[i])
		sprintf(str, ":%s!%s@%s QUIT :Client exited\r\n",
		CNI, CUS, CHO);
	else
		sprintf(str, ":%s!%s@%s QUIT :SelfQuit: %s\r\n",
		CNI, CUS, CHO, &cmd[i]);
	tell_once_all_channel(client, serv, str);
	remove_client(serv, client_fd);
}