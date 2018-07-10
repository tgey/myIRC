/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** fct users
*/

#include "client.h"

void	fct_users(UNUSED client_t *cli, data_serv_t *serv, char *cmd)
{
	int	i = 6;
	char	str[512];

	while (cmd[i] == ' ')
		i += 1;
	sprintf(str, "USERS %s\r\n", &cmd[i]);
	send(serv->server_fd, str, le(str), 0);
}
