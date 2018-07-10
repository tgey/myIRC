/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** fct list
*/

#include "client.h"

void	fct_list(UNUSED client_t *cli, data_serv_t *serv, char *cmd)
{
	int	i = 5;
	char	str[512];

	while (cmd[i] == ' ')
		i += 1;
	sprintf(str, "LIST %s\r\n", &cmd[i]);
	send(serv->server_fd, str, le(str), 0);
}
