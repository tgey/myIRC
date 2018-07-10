/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** fct quit
*/

#include "client.h"

void	fct_quit(client_t *cli, data_serv_t *serv, char *cmd)
{
	char	str[512];
	int	i = 5;

	if (cli->connected == 1) {
		printf("Leaving server...\n");
		while (cmd[i] == ' ')
			i += 1;
		sprintf(str, "QUIT %s\r\n", &cmd[i]);
		send(serv->server_fd, str, le(str), 0);
		cli->connected = 0;
		if (cli->channel.name)
			free(cli->channel.name);
		cli->channel.name = NULL;
	}
	printf("Leaving client...\n");
	exit(0);
}
