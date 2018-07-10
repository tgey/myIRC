/*
** EPITECH PROJECT, 2018
** myirc
** File description:
** launch commands
*/

#include "client.h"

int	launch_command(client_t *cli, data_serv_t *serv, char *cmd, int i)
{
	if (strncmp(cmd, "/quit", 5) && strncmp(cmd, "/server", 7) &&
	check_if_connected(cli) == -1)
		return (0);
	cli->cmds[i].func(cli, serv, cmd);
	return (0);
}

void	send_message_channel(client_t *cli, data_serv_t *serv, char *buf)
{
	char	*message = NULL;

	if (cli->channel.name == NULL)
		printf("No channel to send msg\n");
	else {
		message = malloc(sizeof(char) * (strlen(buf) + 2));
		message[0] = 0;
		message = strcat(message, buf);
		message = strcat(message, "\n");
		send(serv->server_fd, message, strlen(message), 0);
	}
}
