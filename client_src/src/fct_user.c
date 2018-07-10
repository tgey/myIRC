/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** fct user
*/

#include "client.h"

void	fct_user(UNUSED client_t *cli, data_serv_t *serv, char *cmd)
{
	int	i = 5;
	char	str[512];

	while (cmd[i] == ' ')
		i += 1;
	sprintf(str, "USER %s\r\n", &cmd[i]);
	send(serv->server_fd, str, le(str), 0);
}
